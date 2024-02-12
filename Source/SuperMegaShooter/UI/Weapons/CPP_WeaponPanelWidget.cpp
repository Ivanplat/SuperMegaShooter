// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Weapons/CPP_WeaponPanelWidget.h"
#include "UI/Weapons/CPP_WeaponSlotWidget.h"

void UCPP_WeaponPanelWidget::SynchronizeProperties()
{
	UCPP_BaseWidget::SynchronizeProperties();

	if (MainWeaponSlotWidget)
	{
		MainWeaponSlotWidget->WeaponType = EWeaponType::WT_MainWeapon;
	}

	if (SecondaryWeaponSlotWidget)
	{
		SecondaryWeaponSlotWidget->WeaponType = EWeaponType::WT_SecondaryWeapon;
	}

	if (MeleeWeaponSlotWidget)
	{
		MeleeWeaponSlotWidget->WeaponType = EWeaponType::WT_MeleeWeapon;
	}
}
