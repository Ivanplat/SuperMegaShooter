// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/TabStats/CPP_TabStatsWidget.h"
#include "UI/Common/TabStats/CPP_TabPlayerStatsWidget.h"
#include "Components/VerticalBox.h"
#include "Base/Game/CPP_BaseGameState.h"
#include "Player/CPP_PlayerState.h"

void UCPP_TabStatsWidget::NativeConstruct()
{
	UCPP_BaseWidget::NativeConstruct();

	TabPlayerStatsWidgetClassPtr.LoadSynchronous();

	if (TabPlayerStatsWidgetClassPtr.IsValid())
	{
		for (APlayerState* playerState : GetWorld()->GetGameState<ACPP_BaseGameState>()->PlayerArray)
		{
			if (UCPP_TabPlayerStatsWidget* widget = CreateWidget<UCPP_TabPlayerStatsWidget>(GetOwningPlayer(), TabPlayerStatsWidgetClassPtr.Get()))
			{
				widget->SetPlayerState(Cast<ACPP_PlayerState>(playerState));
				VB_Players->AddChildToVerticalBox(widget);
			}
		}
	}

	TabPlayerStatsWidgetClassPtr.Reset();
}
