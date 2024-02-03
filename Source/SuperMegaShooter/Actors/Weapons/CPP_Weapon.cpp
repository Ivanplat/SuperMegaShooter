// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/CPP_Weapon.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "CPP_WeaponWorldMeshActor.h"
#include "CPP_WeaponComponent.h"


ACPP_Weapon::ACPP_Weapon()
{

	CREATE_WEAPON_COMPONENT(WeaponComponent);

	GetSkeletalMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	WeaponInfo.WeaponName = typeid(this).name();

	WeaponAttachType = EWeaponAttachType::WAT_NoOwner;
}

void ACPP_Weapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ACPP_BaseSkeletalMeshActor::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_Weapon, WeaponOwner);
	DOREPLIFETIME(ACPP_Weapon, WeaponAttachType);
	DOREPLIFETIME(ACPP_Weapon, WeaponInfo);
	DOREPLIFETIME(ACPP_Weapon, bWeaponInUse);
}

void ACPP_Weapon::UpdateWeaponOwner(ACPP_BaseCharacter* NewWeaponOwner)
{
	SetOwner(NewWeaponOwner);
	WeaponOwner = NewWeaponOwner;
}

void ACPP_Weapon::UpdateWeaponAttachType(EWeaponAttachType NewAttachType)
{
	WeaponAttachType = NewAttachType;
}

void ACPP_Weapon::Interact_Implementation(ACPP_BaseCharacter* Caller)
{
	if (WeaponOwner) return;
	Caller->GetInventoryComponent()->PickUpWeapon(this);
}

void ACPP_Weapon::MoveCommonWeaponInfo_Implementation(const FWeaponInfo& InWeaponInfo)
{
	WeaponInfo = InWeaponInfo;
}

void ACPP_Weapon::OnWeaponOwnerChanged()
{
	if (WeaponOwner)
	{
		SetActorEnableCollision(false);
		GetSkeletalMeshComponent()->SetSimulatePhysics(false);
	}
	else
	{
		GetSkeletalMeshComponent()->bOwnerNoSee = false;
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		SetActorEnableCollision(true);
	}
}

void ACPP_Weapon::OnWeaponAttachTypeChanged_Implementation()
{
	if (!WeaponOwner) return;

	FName attachingSocketName;

	switch (WeaponAttachType)
	{
	case EWeaponAttachType::WAT_Active:
	{
		attachingSocketName = WeaponInfo.ActiveAttachingSocketName;
	} break;
	case EWeaponAttachType::WAT_Back:
	{
		attachingSocketName = WeaponInfo.BackAttachingSocketName;
	} break;
	}

	AttachToComponent
	(
		WeaponOwner->GetVisibleMesh(),
		FAttachmentTransformRules::SnapToTargetIncludingScale,
		attachingSocketName
	);
}

void ACPP_Weapon::StopUsingWeapon()
{
	bWeaponInUse = false;
}

inline EWeaponAttachType ACPP_Weapon::GetWeaponAttachType() const
{
	return WeaponAttachType;
}

inline ACPP_BaseCharacter* ACPP_Weapon::GetWeaponOwner() const
{
	return WeaponOwner;
}

inline bool ACPP_Weapon::GetWeaponInUse() const
{
	return bWeaponInUse;
}
