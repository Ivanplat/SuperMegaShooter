// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Game/CPP_BaseGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerStart.h"
#include "Player/CPP_PlayerCharacter.h"


void ACPP_BaseGameMode::OnPlayerOrAiJoined(AController* Controller)
{
	const APlayerStart* startPoint = GetRandomStartPoint();

	if (ACPP_BaseCharacter* spawnedCharacter = SpawnPlayerOrAi
	(
		Controller,
		startPoint->GetActorTransform(),
		Cast<APlayerController>(Controller) != nullptr
	))
	{
		Controller->Possess(spawnedCharacter);
	}
}

ACPP_BaseCharacter* ACPP_BaseGameMode::SpawnPlayerOrAi(AController* Controller, const FTransform& SpawnTransorm, bool bPlayer)
{
	return bPlayer ? 
		GetWorld()->SpawnActor<ACPP_BaseCharacter>(PlayerCharacterClass, SpawnTransorm) : 
		GetWorld()->SpawnActor<ACPP_BaseCharacter>(AiCharacterClass, SpawnTransorm);
}

TArray<AActor*> ACPP_BaseGameMode::GetAllStartPoints() const
{
	TArray<AActor*> result;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StartPointClass, result);

	return result;
}

APlayerStart* ACPP_BaseGameMode::GetRandomStartPoint() const
{
	return StartPoints.Num() > 0 ? Cast<APlayerStart>(StartPoints[UKismetMathLibrary::RandomIntegerInRange(0, StartPoints.Num() - 1)]) : nullptr;
}

void ACPP_BaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartPoints = GetAllStartPoints();

	PlayerOrAiJoinedDelegate.AddDynamic(this, &ACPP_BaseGameMode::OnPlayerOrAiJoined);
}

void ACPP_BaseGameMode::MulticastCallGameStartedDelegate_Implementation()
{
	GameStartedDelegate.Broadcast();
}
