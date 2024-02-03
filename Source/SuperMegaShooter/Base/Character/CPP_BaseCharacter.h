// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	virtual void ServerDropWeapon_Implementation();

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Character | Camera")
	virtual inline bool TryGetCharacterLookingVector(FVector& OutVector) const;

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
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCameraComponent* FPCamera;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	USkeletalMeshComponent* FPMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCPP_BaseHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Character Components")
	class UCPP_BaseInventoryComponent* InventoryComponent;
};
