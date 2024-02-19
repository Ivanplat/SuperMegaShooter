// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_BaseHUD.generated.h"

UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void AddKillFeedMessage(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture) {}

	virtual void CreateTabStatsWidget();

	virtual void DestroyTabStatsWidget();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerCharacterReady() {}

	UFUNCTION()
	virtual void OnPlayerCharacterDead() {}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets | Classes")
	TSubclassOf<class UCPP_TabStatsWidget> TabStatsWidgetClassPtr;

	class UCPP_TabStatsWidget* TabStatsWidget;
};
