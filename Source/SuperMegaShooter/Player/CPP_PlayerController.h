// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_PlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCharacterReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerCharacterDead);

UCLASS()
class SUPERMEGASHOOTER_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPP_PlayerController();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Client, Reliable)
	void ClientCallCharacterReadyDelegate();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerCharacterReady();

	UFUNCTION()
	virtual void OnPlayerCharacterDead();

	virtual void ClientCallCharacterReadyDelegate_Implementation();

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerCharacterReady PlayerCharacterReadyDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerCharacterDead PlayerCharacterDeadDelegate;
};
