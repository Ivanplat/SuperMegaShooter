// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Actors/Weapons/CPP_WeaponWorldMeshActor.h"
#include "Actors/Weapons/CPP_WeaponComponent.h"


void UCPP_BaseInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UCPP_BaseCharacterComponent::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCPP_BaseInventoryComponent, SelectedWeapon);
	DOREPLIFETIME(UCPP_BaseInventoryComponent, MainWeapon);
	DOREPLIFETIME(UCPP_BaseInventoryComponent, SecondaryWeapon);
	DOREPLIFETIME(UCPP_BaseInventoryComponent, MeleeWeapon);
}

void UCPP_BaseInventoryComponent::PickUpWeapon(ACPP_Weapon* Weapon)
{
	if (!SelectedWeapon)
	{
		SelectedWeapon = Weapon;
		SelectedWeapon->UpdateWeaponOwner(GetComponentOwner());
		SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Active);
		SelectedWeapon->OnWeaponOwnerChanged();
		SelectedWeapon->OnWeaponAttachTypeChanged();
	}
	else
	{
		if (SelectedWeapon->WeaponInfo.WeaponType == Weapon->WeaponInfo.WeaponType)
		{
			if (TryUpdateSelectedWeapon(Weapon))
			{
				SelectedWeapon->UpdateWeaponOwner(GetComponentOwner());
				SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Active);
				SelectedWeapon->OnWeaponOwnerChanged();
				SelectedWeapon->OnWeaponAttachTypeChanged();
			}
		}
		else
		{
			ACPP_Weapon* updatedWeapon = nullptr;

			switch (Weapon->WeaponInfo.WeaponType)
			{
			case EWeaponType::WT_MainWeapon:      {TryUpdateWeapon(&MainWeapon, Weapon);      updatedWeapon = MainWeapon;      } break;
			case EWeaponType::WT_SecondaryWeapon: {TryUpdateWeapon(&SecondaryWeapon, Weapon); updatedWeapon = SecondaryWeapon; } break;
			case EWeaponType::WT_MeleeWeapon:     {TryUpdateWeapon(&MeleeWeapon, Weapon);     updatedWeapon = MeleeWeapon;     } break;
			}

			if (updatedWeapon)
			{
				updatedWeapon->UpdateWeaponOwner(GetComponentOwner());
				updatedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Back);
				updatedWeapon->OnWeaponOwnerChanged();
				updatedWeapon->OnWeaponAttachTypeChanged();
			}
		}
	}
}

void UCPP_BaseInventoryComponent::DropWeapon(ACPP_Weapon* WeaponToDrop, bool bShouldUpdateSelectedWeapon)
{
	if (WeaponToDrop)
	{
		FVector impulseVector;

		if (!GetComponentOwner()->TryGetCharacterLookingVector(impulseVector))
		{
			return; ////
		}


		WeaponToDrop->WeaponWorldMeshActorClass.LoadSynchronous();

		if (!WeaponToDrop->WeaponWorldMeshActorClass.IsValid()) return;


		FActorSpawnParameters params;
		params.Owner = GetComponentOwner();
		params.Instigator = GetComponentOwner();

		if (ACPP_WeaponWorldMeshActor* meshActor = 
			GetWorld()->SpawnActor<ACPP_WeaponWorldMeshActor>
			(
				WeaponToDrop->WeaponWorldMeshActorClass.Get(),
				WeaponToDrop->GetActorTransform(),
				params
			)
			)
		{
			meshActor->SetWeaponStaticMesh(WeaponToDrop->WeaponStaticMeshPtr);

			meshActor->WeaponClass = WeaponToDrop->GetClass();

			ICPP_WeaponInterface::Execute_MoveCommonWeaponInfo(meshActor, WeaponToDrop->WeaponInfo);
			meshActor->MoveWeaponSkin(WeaponToDrop->GetSkeletalMeshComponent()->GetMaterials());
			meshActor->GetWeaponComponent()->OnWeaponMaterialsChanged();

			meshActor->GetStaticMeshComponent()->AddImpulse
			(
				impulseVector * 400.0f,
				NAME_None,
				true
			);
		}

		WeaponToDrop->WeaponWorldMeshActorClass.Reset();

		switch (WeaponToDrop->WeaponInfo.WeaponType)
		{
			case EWeaponType::WT_MainWeapon:      MainWeapon	  = nullptr; break;
			case EWeaponType::WT_SecondaryWeapon: SecondaryWeapon = nullptr; break;
			case EWeaponType::WT_MeleeWeapon:     MeleeWeapon	  = nullptr; break;
		}

		if (bShouldUpdateSelectedWeapon && WeaponToDrop == SelectedWeapon)
		{
			if (TryUpdateSelectedWeapon())
			{
				SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Active);
				SelectedWeapon->OnWeaponAttachTypeChanged();
			}
		}

		WeaponToDrop->Destroy();
	}
}

inline ACPP_Weapon* UCPP_BaseInventoryComponent::GetSelectedWeapon() const
{
	return SelectedWeapon;
}

inline ACPP_Weapon* UCPP_BaseInventoryComponent::GetMainWeapon() const
{
	return MainWeapon;
}

inline ACPP_Weapon* UCPP_BaseInventoryComponent::GetSecondaryWeapon() const
{
	return SecondaryWeapon;
}

inline ACPP_Weapon* UCPP_BaseInventoryComponent::GetMeleeWeapon() const
{
	return MeleeWeapon;
}

inline ACPP_Weapon* UCPP_BaseInventoryComponent::GetWeaponByWeaponType(EWeaponType WeaponType) const
{
	switch (WeaponType)
	{
	case EWeaponType::WT_MainWeapon:	  return GetMainWeapon();	   break;
	case EWeaponType::WT_SecondaryWeapon: return GetSecondaryWeapon(); break;
	case EWeaponType::WT_MeleeWeapon:	  return GetMeleeWeapon();	   break;
	}
	return nullptr;
}

bool UCPP_BaseInventoryComponent::TryUpdateSelectedWeapon()
{
	if (MainWeapon)
	{
		SelectedWeapon = MainWeapon;
	}
	else if (SecondaryWeapon)
	{
		SelectedWeapon = SecondaryWeapon;
	}
	else if (MeleeWeapon)
	{
		SelectedWeapon = MeleeWeapon;
	}
	else
	{
		SelectedWeapon = nullptr;
	}

	return SelectedWeapon != nullptr;
}

bool UCPP_BaseInventoryComponent::TryUpdateSelectedWeapon(ACPP_Weapon* NewSelectedWeapon)
{
	if (SelectedWeapon)
	{
		DropWeapon(SelectedWeapon, false);
	}

	return (SelectedWeapon = NewSelectedWeapon) != nullptr;
}

bool UCPP_BaseInventoryComponent::TryUpdateWeapon(class ACPP_Weapon** WeaponToUpdate, ACPP_Weapon* NewWeapon)
{
	if (*WeaponToUpdate)
	{
		DropWeapon(*WeaponToUpdate, false);
	}

	*WeaponToUpdate = NewWeapon;

	return *WeaponToUpdate != nullptr;
}

void UCPP_BaseInventoryComponent::SpawnWeaponBySoftPtr(TSoftClassPtr<class ACPP_Weapon> WeaponClass, class ACPP_Weapon** WeaponPtr)
{
	if (WeaponClass.IsValid())
	{
		if (TryUpdateWeapon(WeaponPtr, GetWorld()->SpawnActor<ACPP_Weapon>(WeaponClass.Get())))
		{
			(*WeaponPtr)->UpdateWeaponOwner(GetComponentOwner());
			(*WeaponPtr)->UpdateWeaponAttachType(EWeaponAttachType::WAT_Back);
			(*WeaponPtr)->OnWeaponOwnerChanged();
			(*WeaponPtr)->OnWeaponAttachTypeChanged();
		}
	}
}

void UCPP_BaseInventoryComponent::UnselectWeapon()
{
	if (SelectedWeapon)
	{
		SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Back);
		SelectedWeapon->OnWeaponAttachTypeChanged();
		SelectedWeapon = nullptr;
	}
}

void UCPP_BaseInventoryComponent::ServerSelectWeaponByWeaponType_Implementation(EWeaponType WeaponType)
{
	if (ACPP_Weapon* weapon = GetWeaponByWeaponType(WeaponType))
	{
		if (weapon != GetSelectedWeapon())
		{
			UnselectWeapon();
			if (TryUpdateSelectedWeapon(weapon))
			{
				SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Active);
				SelectedWeapon->OnWeaponAttachTypeChanged();
			}
		}
	}
}

void UCPP_BaseInventoryComponent::SpawnInitialWeaponsSet()
{
	DefaultMainWeaponClass     .LoadSynchronous();
	DefaultSecondaryWeaponClass.LoadSynchronous();
	DefaultMeleeWeaponClass    .LoadSynchronous();

	SpawnWeaponBySoftPtr(DefaultMainWeaponClass,      &MainWeapon);
	SpawnWeaponBySoftPtr(DefaultSecondaryWeaponClass, &SecondaryWeapon);
	SpawnWeaponBySoftPtr(DefaultMeleeWeaponClass,     &MeleeWeapon);

	DefaultMainWeaponClass     .Reset();
	DefaultSecondaryWeaponClass.Reset();
	DefaultMeleeWeaponClass    .Reset();

	if (TryUpdateSelectedWeapon())
	{
		SelectedWeapon->UpdateWeaponAttachType(EWeaponAttachType::WAT_Active);
		SelectedWeapon->OnWeaponAttachTypeChanged();
	}
}

void UCPP_BaseInventoryComponent::SelectWeaponByWeaponType(EWeaponType WeaponType)
{
	ServerSelectWeaponByWeaponType(WeaponType);
}

void UCPP_BaseInventoryComponent::BeginPlay()
{
	UCPP_BaseCharacterComponent::BeginPlay();
}
