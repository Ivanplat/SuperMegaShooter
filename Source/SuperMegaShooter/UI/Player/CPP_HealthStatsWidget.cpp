// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Player/CPP_HealthStatsWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/ActorComponents/CPP_PlayerHealthComponent.h"

void UCPP_HealthStatsWidget::UpdateHealthPercent(float& OutValue)
{
	if (ACPP_PlayerCharacter* playerCharacter = GetOwningPlayerPawn<ACPP_PlayerCharacter>())
	{
		const float currentHealth = static_cast<float>(playerCharacter->GetHealthComponent()->GetHealth());
		OutValue = currentHealth / 100.0f;
	}
	else
	{
		OutValue = 0.0f;
	}
}

void UCPP_HealthStatsWidget::UpdateHealthText(FText& OutValue)
{
	if (ACPP_PlayerCharacter* playerCharacter = GetOwningPlayerPawn<ACPP_PlayerCharacter>())
	{
		const float currentHealth = static_cast<float>(playerCharacter->GetHealthComponent()->GetHealth());
		OutValue = FText::Format(FText::FromString("{0}"), currentHealth);
	}
	else
	{
		OutValue = FText::FromString("0");
	}
}
