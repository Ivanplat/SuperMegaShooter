// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UI/CPP_BaseHUD.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/CPP_PlayerController.h"
#include "Base/Game/CPP_BaseGameMode.h"

void ACPP_BaseHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ACPP_PlayerController* playerController = Cast<ACPP_PlayerController>(GetOwningPlayerController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("123"));
		playerController->PlayerCharacterReadyDelegate.AddDynamic(this, &ACPP_BaseHUD::OnPlayerCharacterReady);
		playerController->PlayerCharacterDeadDelegate.AddDynamic(this, &ACPP_BaseHUD::OnPlayerCharacterDead);
	}
}