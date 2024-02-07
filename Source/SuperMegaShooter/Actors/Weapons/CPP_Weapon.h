// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Actors/CPP_BaseSkeletalMeshActor.h"
#include "WeaponSettings.h"
#include "Interfaces/CPP_WeaponInterface.h"
#include "CPP_Weapon.generated.h"


UCLASS()
class SUPERMEGASHOOTER_API ACPP_Weapon : public ACPP_BaseSkeletalMeshActor, public ICPP_WeaponInterface
{
	GENERATED_BODY()

	friend class ICPP_WeaponInterface;

public:
	ACPP_Weapon();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void UpdateWeaponOwner(class ACPP_BaseCharacter* NewWeaponOwner);

	virtual void UpdateWeaponAttachType(EWeaponAttachType NewAttachType);

	UFUNCTION()
	virtual void OnWeaponOwnerChanged();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWeaponAttachTypeChanged();

	virtual void UseWeapon() {}

	virtual void StopUsingWeapon();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon | Settings")
	virtual inline EWeaponAttachType GetWeaponAttachType() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon | Settings")
	virtual inline ACPP_BaseCharacter* GetWeaponOwner() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon | Settings")
	virtual inline bool GetWeaponInUse() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon | Settings")
	virtual inline EWeaponId GetWeaponId() const;

	DECLARE_GET_WEAPON_COMPONENT_METHODE();

protected:
	virtual void Interact_Implementation(class ACPP_BaseCharacter* Caller) override;

	virtual void MoveCommonWeaponInfo_Implementation(const FWeaponInfo& InWeaponInfo) override;

	virtual bool TryUseWeapon() { return true; }

	virtual bool IsAbleToUseWeapon() const { return true; }

	UFUNCTION(NetMulticast, Reliable)
	void PlayWeaponAnimationMulticast(EWeaponAnimationType AnimationType);

	virtual void PlayWeaponAnimationMulticast_Implementation(EWeaponAnimationType AnimationType) {}

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Weapon | Settings")
	FWeaponInfo WeaponInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Classes")
	TSoftClassPtr<class ACPP_WeaponWorldMeshActor> WeaponWorldMeshActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	UStaticMesh* WeaponStaticMeshPtr;

protected:
	UPROPERTY(Replicated, ReplicatedUsing = OnWeaponOwnerChanged)
	class ACPP_BaseCharacter* WeaponOwner;

	UPROPERTY(Replicated, ReplicatedUsing = OnWeaponAttachTypeChanged)
	EWeaponAttachType WeaponAttachType;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Components")
	class UCPP_WeaponComponent* WeaponComponent;

	UPROPERTY(Replicated)
	bool bWeaponInUse = false;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	int32 Damage = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	TSubclassOf<UDamageType> WeaponDamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	EWeaponId WeaponId;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* IdleAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* UsingAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* InspectionAnimation;
};
