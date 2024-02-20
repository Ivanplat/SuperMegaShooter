// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSettings.generated.h"

USTRUCT(BlueprintType)
struct SUPERMEGASHOOTER_API FDamageWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Settings")
	int32 WeaponDamage;
};

USTRUCT(BlueprintType)
struct SUPERMEGASHOOTER_API FFireWeaponInfo : public FDamageWeaponInfo
{
	GENERATED_BODY()


};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_MainWeapon      UMETA(DisplayName = "Main Weapon"),
	WT_SecondaryWeapon UMETA(DisplayName = "Secondary Weapon"),
	WT_MeleeWeapon     UMETA(DisplayName = "Melee Weapon")
};


USTRUCT(BlueprintType)
struct SUPERMEGASHOOTER_API FWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	FString WeaponName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	FName ActiveAttachingSocketName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	FName BackAttachingSocketName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	EWeaponType WeaponType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	UTexture2D* WeaponUITexture = nullptr;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Weapon Info")
	UTexture2D* WeaponUIKillFeedTexture = nullptr;
};

UENUM(BlueprintType)
enum class EWeaponAttachType : uint8
{
	WAT_Active  UMETA(DisplayName = "Active"),
	WAT_Back    UMETA(DisplayName = "Back"),
	WAT_NoOwner UMETA(DisplayName = "No Owner")
};

UENUM(BlueprintType)
enum class EWeaponAnimationType : uint8
{
	WAnT_Idle		UMETA(DisplayName = "Idle"),
	WAnT_Using		UMETA(DisplayName = "Using"),
	WAnT_Reloading  UMETA(DisplayName = "Reloading"),
	WAnT_Inspection UMETA(DisplayName = "Inspection"),
	WAnT_Preparing  UMETA(DisplayName = "Preparing")
};

UENUM(BlueprintType)
enum class EWeaponId : uint8
{
	WId_Ak	  UMETA(DisplayName = "Ak"),
	WId_Glock UMETA(DisplayName = "Glock"),
	WId_Knife UMETA(DisplayName = "Knife"),
	WId_Unset UMETA(DisplayName = "Unset")
};

UENUM(BlueprintType)
enum class EWeaponSoundType : uint8
{
	WST_Using      UMETA(DisplayName = "Using"),
	WST_Preparing  UMETA(DisplayName = "Preparing"),
	WST_Reloading  UMETA(DisplayName = "Reloading")
};

enum class EWeaponRecoilType : uint8
{
	WRT_Up    = 0b0001,
	WRT_Right = 0b0010,
	WRT_Down  = 0b0100,
	WRT_Left  = 0b1000
};

USTRUCT(BlueprintType)
struct FFireWeaponRecoilInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Recoil Info")
	float Force = 0.35f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Recoil Info")
	uint8 RecoilType = 0;
};