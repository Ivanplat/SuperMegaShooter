// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerController.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "Base/UI/CPP_BaseHUD.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "Player/CPP_PlayerState.h"


ACPP_PlayerController::ACPP_PlayerController()
{
	PlayerCharacterReadyDelegate.AddDynamic(this, &ACPP_PlayerController::OnPlayerCharacterReady);
	PlayerCharacterDeadDelegate.AddDynamic(this, &ACPP_PlayerController::OnPlayerCharacterDead);
	PlayerDeadDelegate.AddDynamic(this, &ACPP_PlayerController::OnPlayerDead); 
}

void ACPP_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACPP_BaseGameMode* gameMode = GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>())
	{
		gameMode->PlayerOrAiJoinedDelegate.Broadcast(this);
	}
}

void ACPP_PlayerController::OnPlayerCharacterReady()
{

}

void ACPP_PlayerController::OnPlayerCharacterDead()
{

}

void ACPP_PlayerController::ClientCallCharacterReadyDelegate_Implementation()
{
	PlayerCharacterReadyDelegate.Broadcast();
}

void ACPP_PlayerController::OnPlayerDead(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture)
{
	for (APlayerState* state : GetWorld()->GetGameState<AGameStateBase>()->PlayerArray)
	{
		Cast<ACPP_PlayerState>(state)->ClientNotifyKillFeed(KillerName, VictimName, DeathCauserUITexture);
	}
}