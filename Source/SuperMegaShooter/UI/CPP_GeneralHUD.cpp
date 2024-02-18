// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPP_GeneralHUD.h"
#include "UI/Common/CPP_MainUIWidget.h"
#include "UI/Common/KillFeed/CPP_KillFeedWidget.h"
#include "UI/Common/KillFeed/CPP_KillFeedMessageWidget.h"
#include "GameFramework/PlayerState.h"
#include "Actors/Weapons/CPP_Weapon.h"

inline UCPP_MainUIWidget* ACPP_GeneralHUD::GetMainUIWidget() const
{
	return MainUIWidget;
}

void ACPP_GeneralHUD::AddKillFeedMessage(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture)
{
	if (UCPP_KillFeedMessageWidget* widget = CreateWidget<UCPP_KillFeedMessageWidget>(GetOwningPlayerController(), KillFeedMessageWidgetClass))
	{
		widget
			->SetKillerNickname(FText::FromString(KillerName))
			->SetVictimNickname(FText::FromString(VictimName))
			->SetWeponImageTexture(DeathCauserUITexture);

		GetMainUIWidget()->GetKillFeedWidget()->AddKillFeedMessage(widget);
	}
}

void ACPP_GeneralHUD::CreateMainUIWidget()
{
	if (!MainUIWidget && MainUIWidgetClass != nullptr && GetOwningPlayerController())
	{
		MainUIWidget = CreateWidget<UCPP_MainUIWidget>(GetOwningPlayerController(), MainUIWidgetClass);
		MainUIWidget->AddToViewport();
	}
}

void ACPP_GeneralHUD::DestroyMainUIWidget()
{
	if (MainUIWidget)
	{
		MainUIWidget->RemoveFromParent();
		MainUIWidget = nullptr;
	}
}

void ACPP_GeneralHUD::OnPlayerCharacterReady()
{
	CreateMainUIWidget();
}

void ACPP_GeneralHUD::OnPlayerCharacterDead()
{
	DestroyMainUIWidget();
}
