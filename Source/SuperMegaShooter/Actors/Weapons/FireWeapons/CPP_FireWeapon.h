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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void UseWeapon() override;

	virtual void StopUsingWeapon() override;

protected:
	virtual bool TryUseWeapon() override;

	virtual bool AbleToUseWeapon() override;

	virtual void Fire();

	virtual void DecreaseAmmo();

	virtual void PlayWeaponAnimationMulticast_Implementation(EWeaponAnimationType AnimationType) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 CurrentAmmoInBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 MaxCurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings", Replicated)
	int32 MaxAmmoInBack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	bool bAbleToAutoFire = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	float FireDelay = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire Weapon Settings")
	FTimerHandle AutoFireTimeHandler;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* ReloadingAnimation;
};
