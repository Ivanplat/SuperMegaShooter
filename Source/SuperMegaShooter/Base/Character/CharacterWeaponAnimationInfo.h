// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/WeaponSettings.h"
#include "CharacterWeaponAnimationInfo.generated.h"

USTRUCT(BlueprintType)
struct SUPERMEGASHOOTER_API FCharacterWeaponAnimationInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	static void GetAnimationNameByType(FName& OutAnimationName, EWeaponAnimationType AnimationType);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Weapon Animation Info")
	TMap<FName, UAnimMontage*> CharacterWeaponMontage;
};

USTRUCT(BlueprintType)
struct SUPERMEGASHOOTER_API FCharacterWeaponAnimationInfoMap : public FTableRowBase
{
	GENERATED_BODY()
public:
	static void GetRowNameByWeaponId(FName& OutRowName, EWeaponId WeaponId);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Weapon Animation Info Map")
	FCharacterWeaponAnimationInfo CharacterWeaponMontages;

};
