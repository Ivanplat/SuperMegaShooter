// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "Actors/Weapons/WeaponSettings.h"
#include "CPP_WeaponSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_WeaponSlotWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon Slot Widgte | Player")
	inline class ACPP_Weapon* GetWeapon() const;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	FSlateBrush UpdateBackgroundColor();

	UFUNCTION(BlueprintCallable)
	FText UpdateWeaponAmmoText();

	UFUNCTION(BlueprintCallable)
	FSlateBrush UpdateWeaponImage();

public:
	EWeaponType WeaponType;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* T_WeaponAmmo = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* I_WeaponImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UBorder* B_Background = nullptr;
};
