// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CPP_BaseGameState.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State | Time")
	virtual inline int32 GetSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game State | Time")
	virtual inline int32 GetMinutes() const;

protected:
	UFUNCTION()
	virtual void OnGameStarted();

	UFUNCTION()
	virtual void OnGameOver();

	UFUNCTION()
	virtual void UpdateRoundTime();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Game State | Time")
	int32 Seconds = 59;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Game State | Time")
	int32 Minutes = 1;

	UPROPERTY()
	FTimerHandle UpdateRoundTimeTimerHandle;
};
