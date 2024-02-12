// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Weapons/WeaponSettings.h"
#include "CPP_BaseCharacter.generated.h"

UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_BaseCharacter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Base Character")
	void ServerInteract();

	virtual void ServerInteract_Implementation();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Base Character")
	void ServerDropWeapon();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Base Character")
	void ServerReloadWeapon();

	virtual void ServerDropWeapon_Implementation();

	virtual void MulticastPlayCharaterWeaponMontage_Implementation(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float NeededTime = -1.0f);

	virtual void MulticastStopPlayCharacterWeaponMontage_Implementation(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float BlendTime = 1.0f);

	virtual void ServerReloadWeapon_Implementation();

	virtual void StartCrouch();

	virtual void StopCrouching();

	virtual void SelectMainWeapon();

	virtual void SelectSecondaryWeapon();

	virtual void SelectMeleeWeapon();

	inline void CalculateLookingVerticalAngle();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Components")
	virtual inline USkeletalMeshComponent* GetVisibleMesh() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Components")
	virtual inline USkeletalMeshComponent* GetFPMesh() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Components")
	virtual inline class UCPP_BaseHealthComponent* GetHealthComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Components")
	virtual inline class UCPP_BaseInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Components")
	virtual inline class UCameraComponent* GetFPCamera() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Character | Camera")
	virtual inline bool TryGetCharacterLookingVector(FVector& OutVector) const;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayCharaterWeaponMontage(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float NeededTime = -1.0f);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStopPlayCharacterWeaponMontage(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float BlendTime = 1.0f);

	template<class T>
	inline T* GetHealthComponent() const
	{
		return Cast<T>(GetHealthComponent());
	}

	template<class T>
	inline T* GetInventoryComponent() const
	{
		return Cast<T>(GetInventoryComponent());
	}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCameraComponent* FPCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCPP_BaseHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCPP_BaseInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UDataTable* CharacterWeaponAnimationsDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Character")
	double LookingVerticalAngle;
};
