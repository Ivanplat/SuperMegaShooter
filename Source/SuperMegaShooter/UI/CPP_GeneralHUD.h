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
	inline class UCPP_MainUIWidget* GetMainUIWidget() const;

protected:
	virtual void CreateMainUIWidget();

	virtual void DestroyMainUIWidget();

	virtual void OnPlayerCharacterReady();

	virtual void OnPlayerCharacterDead();

protected:
	class UCPP_MainUIWidget* MainUIWidget;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerHUD | Widgets | Classes")
	TSubclassOf<class UCPP_MainUIWidget> MainUIWidgetClass;
};
