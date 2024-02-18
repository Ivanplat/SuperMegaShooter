// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "CPP_FireWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_FireWeapon : public ACPP_Weapon
{
	GENERATED_BODY()

public:
	ACPP_FireWeapon();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void UseWeapon() override;

	virtual void StopUsingWeapon() override;

	virtual void Reload();

	virtual void ManualStopReloading();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Fire Weapon | Settings")
	virtual inline bool IsReloading() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Fire Weapon | Settings")
	virtual inline int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Fire Weapon | Settings")
	virtual inline int32 GetCurrentAmmoInBack() const;

protected:
	virtual bool TryUseWeapon() override;

	virtual bool IsAbleToUseWeapon() const override;

	virtual void Fire();

	virtual void DecreaseAmmo();

	virtual void PlayWeaponAnimationMulticast_Implementation(EWeaponAnimationType AnimationType) override;

	virtual bool IsAbleToReload() const;

	UFUNCTION()
	virtual void EndReloading();

	virtual bool IsNeededToReload() const;

	virtual void PlayUsingWeaponEffects_Implementation() override;


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 CurrentAmmoInBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 MaxCurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 MaxAmmoInBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	bool bReloading = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	bool bAbleToAutoFire = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	float FireDelay = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	float ReloadingTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* ReloadingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Components")
	USceneComponent* GunFirePoint;

	UPROPERTY()
	FTimerHandle AutoFireTimeHandler;

	UPROPERTY()
	FTimerHandle ReloadingTimerHandler;

	UPROPERTY()
	UAudioComponent* ReloadingAudioComponent;
};
