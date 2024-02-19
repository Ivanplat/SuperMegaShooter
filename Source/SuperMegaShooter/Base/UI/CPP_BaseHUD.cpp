// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/UI/CPP_BaseHUD.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/CPP_PlayerController.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "GameFramework/PlayerState.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "UI/Common/KillFeed/CPP_KillFeedMessageWidget.h"
#include "UI/Common/KillFeed/CPP_KillFeedWidget.h"
#include "UI/Common/TabStats/CPP_TabStatsWidget.h"


void ACPP_BaseHUD::CreateTabStatsWidget()
{
	if (!TabStatsWidget && TabStatsWidgetClassPtr)
	{
		TabStatsWidget = CreateWidget<UCPP_TabStatsWidget>(GetOwningPlayerController(), TabStatsWidgetClassPtr);

		if (TabStatsWidget)
		{
			TabStatsWidget->AddToViewport();
		}
	}
}

void ACPP_BaseHUD::DestroyTabStatsWidget()
{
	if (TabStatsWidget)
	{
		TabStatsWidget->RemoveFromParent();
		TabStatsWidget = nullptr;
	}
}

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