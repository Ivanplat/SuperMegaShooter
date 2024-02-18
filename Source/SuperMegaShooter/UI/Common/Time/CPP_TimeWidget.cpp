// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/Time/CPP_TimeWidget.h"
#include "Components/TextBlock.h"
#include "Base/Game/CPP_BaseGameState.h"

void UCPP_TimeWidget::UpdateTimeText(FText& OutValue)
{
	if (ACPP_BaseGameState* gameState = GetWorld()->GetGameState<ACPP_BaseGameState>())
	{
		const int32 minutes = gameState->GetMinutes();
		const int32 seconds = gameState->GetSeconds();

		FText minutesText, secondsText;

		if (minutes < 10)
		{
			minutesText = FText::Format(FText::FromString("0{0}"), minutes);
		}
		else
		{
			minutesText = FText::Format(FText::FromString("{0}"), minutes);
		}

		if(seconds < 10)
		{
			secondsText = FText::Format(FText::FromString("0{0}"), seconds);
		}
		else
		{
			secondsText = FText::Format(FText::FromString("{0}"), seconds);
		}

		OutValue = FText::Format(FText::FromString("{0}:{1}"), minutesText, secondsText);
	}
	else
	{
		OutValue = FText::FromString("");
	}
}
