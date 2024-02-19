// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_TabPlayerStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_TabPlayerStatsWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetPlayerState(class ACPP_PlayerState* NewPlayerState);

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab Player Stats Widgets | Stats")
	virtual void GetPlayerPingText(FText& OutValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab Player Stats Widgets | Stats")
	virtual void GetPlayerNicknameText(FText& OutValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab Player Stats Widgets | Stats")
	virtual void GetPlayerKillsText(FText& OutValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab Player Stats Widgets | Stats")
	virtual void GetPlayerDeathsText(FText& OutValue);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab Player Stats Widgets | Stats")
	virtual void GetPlayerKdText(FText& OutValue);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_PlayerPing;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_PlayerNickname;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_PlayerKills;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_PlayerDeats;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Kd;

	class ACPP_PlayerState* PlayerState;
};
