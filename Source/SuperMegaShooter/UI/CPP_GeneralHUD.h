// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseHUD.h"
#include "CPP_GeneralHUD.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_GeneralHUD : public ACPP_BaseHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerHUD | Widgets")
	class UCPP_MainUIWidget* GetMainUIWidget() const;

	virtual void AddKillFeedMessage(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture) override;

protected:
	virtual void CreateMainUIWidget();

	virtual void DestroyMainUIWidget();

	virtual void OnPlayerCharacterReady() override;

	virtual void OnPlayerCharacterDead() override;

protected:
	class UCPP_MainUIWidget* MainUIWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerHUD | Widgets | Classes")
	TSubclassOf<class UCPP_MainUIWidget> MainUIWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerHUD | Widgets | Classes")
	TSubclassOf<class UCPP_KillFeedMessageWidget> KillFeedMessageWidgetClass;
};
