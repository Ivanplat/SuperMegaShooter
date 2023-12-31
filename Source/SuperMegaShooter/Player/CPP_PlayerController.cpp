// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerController.h"
#include "Base/Game/CPP_BaseGameMode.h"


void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ACPP_BaseGameMode* gameMode = GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>())
	{
		gameMode->PlayerOrAiJoinedDelegate.Broadcast(this);
	}
}
