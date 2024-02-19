// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/TabStats/CPP_TabPlayerStatsWidget.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/CPP_PlayerState.h"
#include "Components/TextBlock.h"

void UCPP_TabPlayerStatsWidget::GetPlayerPingText(FText& OutValue)
{
	if (PlayerState)
	{
		OutValue = FText::FromString
		(
			FString::FromInt
			(
				static_cast<int32>(PlayerState->GetPingInMilliseconds() / 100.0f)
			)
		);
	}
	else
	{
		OutValue = FText::FromString("");
	}
}

void UCPP_TabPlayerStatsWidget::GetPlayerNicknameText(FText& OutValue)
{
	if (PlayerState)
	{
		OutValue = FText::FromString(PlayerState->GetPlayerName());
	}
	else
	{
		OutValue = FText::FromString("");
	}
}

void UCPP_TabPlayerStatsWidget::GetPlayerKillsText(FText& OutValue)
{
	if (PlayerState)
	{
		OutValue = FText::FromString(FString::FromInt(PlayerState->GetKills()));
	}
	else
	{
		OutValue = FText::FromString("");
	}
}

void UCPP_TabPlayerStatsWidget::GetPlayerDeathsText(FText& OutValue)
{
	if (PlayerState)
	{
		OutValue = FText::FromString(FString::FromInt(PlayerState->GetDeaths()));
	}
	else
	{
		OutValue = FText::FromString("");
	}
}

void UCPP_TabPlayerStatsWidget::GetPlayerKdText(FText& OutValue)
{
	if (PlayerState)
	{
		const float kills = static_cast<float>(PlayerState->GetKills());
		const float deaths = static_cast<float>(PlayerState->GetDeaths());

		OutValue = FText::FromString(FString::SanitizeFloat(kills/ deaths));
	}
	else
	{
		OutValue = FText::FromString("");
	}
}

void UCPP_TabPlayerStatsWidget::SetPlayerState(ACPP_PlayerState* NewPlayerState)
{
	PlayerState = NewPlayerState;
}
