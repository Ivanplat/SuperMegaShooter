// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActorComponents/Character/CPP_BaseCharacterComponent.h"
#include "CPP_BaseInventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_BaseInventoryComponent : public UCPP_BaseCharacterComponent
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PickUpWeapon(class ACPP_Weapon* Weapon);

	virtual void DropWeapon(class ACPP_Weapon* WeaponToDrop, bool bShouldUpdateSelectedWeapon = true);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Component | Weapons")
	virtual inline class ACPP_Weapon* GetSelectedWeapon() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Component | Weapons")
	virtual inline class ACPP_Weapon* GetMainWeapon() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Component | Weapons")
	virtual inline class ACPP_Weapon* GetSecondaryWeapon() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Component | Weapons")
	virtual inline class ACPP_Weapon* GetMeleeWeapon() const;

	virtual void SpawnInitialWeaponsSet();

protected:

	virtual bool TryUpdateSelectedWeapon();

	virtual bool TryUpdateSelectedWeapon(class ACPP_Weapon* NewSelectedWeapon);

	virtual bool TryUpdateWeapon(class ACPP_Weapon** WeaponToUpdate, class ACPP_Weapon* NewWeapon);

	virtual void SpawnWeaponBySoftPtr(TSoftClassPtr<class ACPP_Weapon> WeaponClass, class ACPP_Weapon** WeaponPtr);

	virtual void BeginPlay() override;

protected:
	UPROPERTY(Replicated)
	class ACPP_Weapon* SelectedWeapon;

	UPROPERTY(Replicated)
	class ACPP_Weapon* MainWeapon;

	UPROPERTY(Replicated)
	class ACPP_Weapon* SecondaryWeapon;

	UPROPERTY(Replicated)
	class ACPP_Weapon* MeleeWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Invenotory Component | Weapons | Classes")
	TSoftClassPtr<ACPP_Weapon> DefaultMainWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Invenotory Component | Weapons | Classes")
	TSoftClassPtr<ACPP_Weapon> DefaultSecondaryWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Invenotory Component | Weapons | Classes")
	TSoftClassPtr<ACPP_Weapon> DefaultMeleeWeaponClass;
};
