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

	virtual void UpdateWeaponOwner(class ACPP_BaseCharacter* NewWeaponOwner, bool bShouldUpdateNetwork = true);

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon | Settings")
	virtual inline int32 GetWeaponDamage() const;

	DECLARE_GET_WEAPON_COMPONENT_METHODE();

	virtual void PrepareWeapon(bool bShouldDelay = false);

protected:
	virtual void Interact_Implementation(class ACPP_BaseCharacter* Caller) override;

	virtual void MoveCommonWeaponInfo_Implementation(const FWeaponInfo& InWeaponInfo) override;

	virtual bool TryUseWeapon() { return true; }

	virtual bool IsAbleToUseWeapon() const { return true; }

	UFUNCTION(NetMulticast, Reliable)
	void PlayWeaponAnimationMulticast(EWeaponAnimationType AnimationType);

	virtual void PlayWeaponAnimationMulticast_Implementation(EWeaponAnimationType AnimationType) {}

	virtual void PlayPreparingAnimation(const float Delay);

	UFUNCTION(NetMulticast, Reliable)
	void PlayWeaponSoundByType(EWeaponSoundType WeaponSoundType);

	UFUNCTION(NetMulticast, Reliable)
	void PlayUsingWeaponEffects();

	virtual void PlayWeaponSoundByType_Implementation(EWeaponSoundType WeaponSoundType);

	virtual void PlayUsingWeaponEffects_Implementation() {}

	virtual void PlayWeaponSound(USoundBase* Sound);

	UFUNCTION()
	virtual void UnlockWeapon();


	inline FName GetSoundTypeName(EWeaponSoundType SoundType)
	{
		switch (SoundType)
		{
		case EWeaponSoundType::WST_Using:	  return FName("Using");	 break;
		case EWeaponSoundType::WST_Preparing: return FName("Preparing"); break;
		case EWeaponSoundType::WST_Reloading: return FName("Reloading"); break;
		}
		return FName("Invalid type");
	}

	UFUNCTION(NetMulticast, Reliable)
	void StopPlayingAudioComponents();

	virtual void StopPlayingAudioComponents_Implementation();

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, Category = "Weapon | Settings")
	FWeaponInfo WeaponInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Classes")
	TSoftClassPtr<class ACPP_WeaponWorldMeshActor> WeaponWorldMeshActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	UStaticMesh* WeaponStaticMeshPtr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Sound")
	TMap<FName, USoundBase*> WeaponSounds;

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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings", Replicated)
	bool bWeaponLocked = true;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings")
	float PreparingTime = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* IdleAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* UsingAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* InspectionAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Animations")
	UAnimationAsset* PreparingAnimation;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Settings | Effects")
	UParticleSystem* UsingParticleSystemTemplate;

	UPROPERTY()
	UAudioComponent* ClientAudioComponent;

	UPROPERTY()
	UAudioComponent* OthersAudioComponent;
};
