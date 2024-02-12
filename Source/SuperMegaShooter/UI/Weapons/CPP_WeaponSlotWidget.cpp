// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Weapons/CPP_WeaponSlotWidget.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/ActorComponents/CPP_PlayerInventoryComponent.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Actors/Weapons/FireWeapons/CPP_FireWeapon.h"

inline ACPP_Weapon* UCPP_WeaponSlotWidget::GetWeapon() const
{
	if (ACPP_PlayerCharacter* playerCharacter = GetOwningPlayerPawn<ACPP_PlayerCharacter>())
	{
		UCPP_PlayerInventoryComponent* inventoryComponent = playerCharacter->GetInventoryComponent<UCPP_PlayerInventoryComponent>();

		switch (WeaponType)
		{
		case EWeaponType::WT_MainWeapon:	  return inventoryComponent->GetMainWeapon();      break;
		case EWeaponType::WT_SecondaryWeapon: return inventoryComponent->GetSecondaryWeapon(); break;
		case EWeaponType::WT_MeleeWeapon:	  return inventoryComponent->GetMeleeWeapon();     break;
		}
	}

	return nullptr;
}

void UCPP_WeaponSlotWidget::NativeConstruct()
{
	UCPP_BaseWidget::NativeConstruct();
}

FSlateBrush UCPP_WeaponSlotWidget::UpdateBackgroundColor()
{
	FSlateBrush sb;

	if (ACPP_PlayerCharacter* playerCharacter = GetOwningPlayerPawn<ACPP_PlayerCharacter>())
	{
		UCPP_PlayerInventoryComponent* inventoryComponent = playerCharacter->GetInventoryComponent<UCPP_PlayerInventoryComponent>();

		FLinearColor lc =
			(
				GetWeapon() && GetWeapon() == inventoryComponent->GetSelectedWeapon() ?
				FLinearColor(100.0f, 100.0f, 100.0f, 0.5f)
				:
				FLinearColor(0.0f, 0.0f, 0.0f, 0.5f)
				);

		sb.TintColor = lc;
	}
	return sb;
}

FText UCPP_WeaponSlotWidget::UpdateWeaponAmmoText()
{
	if (ACPP_FireWeapon* fireWeapon = Cast<ACPP_FireWeapon>(GetWeapon()))
	{
		return FText::Format(FText::FromString("{0}/{1}"), fireWeapon->GetCurrentAmmo(), fireWeapon->GetCurrentAmmoInBack());
	}
	else
	{
		return FText::FromString("");
	}
}

FSlateBrush UCPP_WeaponSlotWidget::UpdateWeaponImage()
{
	FSlateBrush sb;

	if (ACPP_Weapon* weapon = GetWeapon())
	{
		sb.SetResourceObject(weapon->WeaponInfo.WeaponUITexture);
		sb.TintColor = FLinearColor::White;
	}

	return sb;
}
