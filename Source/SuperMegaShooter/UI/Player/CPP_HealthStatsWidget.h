// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_HealthStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_HealthStatsWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateHealthPercent(float& OutValue);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateHealthText(FText& OutValue);

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Health;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Health;
};
