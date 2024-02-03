// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Actors/Weapons/WeaponSettings.h"
#include "CPP_WeaponInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCPP_WeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class SUPERMEGASHOOTER_API ICPP_WeaponInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void MoveCommonWeaponInfo(const FWeaponInfo& InWeaponInfo);

	UFUNCTION(BlueprintNativeEvent)
	void MoveFireWeaponInfo(const FFireWeaponInfo& InFireWeaponInfo);

	UFUNCTION()
	virtual void MoveWeaponSkin(const TArray<UMaterialInterface*>& InWeaponMaterials);

	virtual inline class UCPP_WeaponComponent* GetWeaponComponent() const;

	template<class T>
	inline T* GetWeaponComponent() const
	{
		return Cast<T>(GetWeaponComponent());
	}
};

#define CREATE_WEAPON_COMPONENT(WeaponComponent) \
WeaponComponent = CreateDefaultSubobject<UCPP_WeaponComponent>(TEXT("WeaponComponent")); \
check(WeaponComponent); \
WeaponComponent->SetIsReplicated(true);

#define DECLARE_GET_WEAPON_COMPONENT_METHODE() \
UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")\
inline class UCPP_WeaponComponent* GetWeaponComponent() const override {return ICPP_WeaponInterface::GetWeaponComponent();};