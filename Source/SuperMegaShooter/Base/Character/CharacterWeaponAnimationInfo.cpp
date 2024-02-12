// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/CharacterWeaponAnimationInfo.h"


void FCharacterWeaponAnimationInfoMap::GetRowNameByWeaponId(FName& OutRowName, EWeaponId WeaponId)
{
	switch (WeaponId)
	{
		case EWeaponId::WId_Ak:    OutRowName = "Ak";    break;
		case EWeaponId::WId_Glock: OutRowName = "Glock"; break;
		case EWeaponId::WId_Knife: OutRowName = "Knife"; break;
		case EWeaponId::WId_Unset: OutRowName = "Unset"; break;
	}
}

void FCharacterWeaponAnimationInfo::GetAnimationNameByType(FName& OutAnimationName, EWeaponAnimationType AnimationType)
{
	switch (AnimationType)
	{
		case EWeaponAnimationType::WAnT_Idle:		OutAnimationName = "Idle";		 break;
		case EWeaponAnimationType::WAnT_Using:		OutAnimationName = "Using";		 break;
		case EWeaponAnimationType::WAnT_Reloading:  OutAnimationName = "Reloading";  break;
		case EWeaponAnimationType::WAnT_Inspection: OutAnimationName = "Inspection"; break;
		case EWeaponAnimationType::WAnT_Preparing:  OutAnimationName = "Preparing";  break;
	}
}
