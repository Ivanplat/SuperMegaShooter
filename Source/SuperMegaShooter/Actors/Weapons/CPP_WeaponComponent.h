// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERMEGASHOOTER_API UCPP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class ICPP_WeaponInterface;

public:	
	UCPP_WeaponComponent();

public:
	UFUNCTION()
	void OnWeaponMaterialsChanged();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(Replicated, ReplicatedUsing = OnWeaponMaterialsChanged)
	TArray<UMaterialInterface*> WeaponMaterials;
};
