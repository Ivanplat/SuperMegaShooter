// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPP_PlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerKilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDead);

UCLASS()
class SUPERMEGASHOOTER_API ACPP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACPP_PlayerState();
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player State | Stats")
	virtual inline int32 GetKills() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Player State | Stats")
	virtual inline int32 GetDeaths() const;

	UFUNCTION(Client, Reliable)
	void ClientNotifyKillFeed(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture);

protected:
	UFUNCTION()
	virtual void OnPlayerKilled();

	UFUNCTION()
	virtual void OnPlayerDead();

	virtual void ClientNotifyKillFeed_Implementation(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture);

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerKilled PlayerKilledDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerDead PlayerDeadDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Player State | Stats")
	int32 Kills = 0;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Player State | Stats")
	int32 Deaths = 0;
};
