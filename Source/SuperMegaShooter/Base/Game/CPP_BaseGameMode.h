// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_BaseGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerOrAiJoined, AController*, Controller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStarted);

UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Start Game")
	virtual void OnPlayerOrAiJoined(AController* Controller);

	virtual class ACPP_BaseCharacter* SpawnPlayerOrAi(AController* Controller, const FTransform& SpawnTransorm, bool bPlayer = true);

	virtual TArray<AActor*> GetAllStartPoints() const;

	virtual class APlayerStart* GetRandomStartPoint() const;

	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastCallGameStartedDelegate();

	virtual void MulticastCallGameStartedDelegate_Implementation();

public:

	UPROPERTY(BlueprintAssignable, Category = "Start Game")
	FPlayerOrAiJoined PlayerOrAiJoinedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Start Game")
	FGameStarted GameStartedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Start Game | Spawn")
	TSubclassOf<class APlayerStart> StartPointClass;

	UPROPERTY(EditDefaultsOnly, Category = "Start Game | Spawn")
	TSubclassOf<class ACPP_PlayerCharacter> PlayerCharacterClass;

	UPROPERTY(EditDefaultsOnly, Category = "Start Game | Spawn")
	TSubclassOf<class ACPP_BaseCharacter> AiCharacterClass;

	UPROPERTY()
	TArray<AActor*> StartPoints;
};
