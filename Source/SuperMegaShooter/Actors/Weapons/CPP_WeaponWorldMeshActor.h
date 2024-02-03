// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Actors/CPP_BaseStaticMeshActor.h"
#include "Interfaces/CPP_InteractionInterface.h"
#include "Interfaces/CPP_WeaponInterface.h"
#include "WeaponSettings.h"
#include "CPP_WeaponWorldMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_WeaponWorldMeshActor : public ACPP_BaseStaticMeshActor, public ICPP_InteractionInterface,
	public ICPP_WeaponInterface
{
	GENERATED_BODY()

	friend class ICPP_WeaponInterface;
	
public:
	ACPP_WeaponWorldMeshActor();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	DECLARE_GET_WEAPON_COMPONENT_METHODE();

	UFUNCTION(NetMulticast, Reliable)
	void SetWeaponStaticMesh(UStaticMesh* NewStaticMesh);

protected:
	virtual void Interact_Implementation(class ACPP_BaseCharacter* Caller) override;

	virtual void MoveCommonWeaponInfo_Implementation(const FWeaponInfo& InWeaponInfo) override;

	virtual void SetWeaponStaticMesh_Implementation(UStaticMesh* NewStaticMesh);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponMeshSimulatePhysics(bool bSimulate);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Classes")
	TSoftClassPtr<class ACPP_Weapon> WeaponClass;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Components")
	class UBoxComponent* WeaponCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Components")
	class UCPP_WeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Weapon | Settings")
	FWeaponInfo WeaponInfo;
};
