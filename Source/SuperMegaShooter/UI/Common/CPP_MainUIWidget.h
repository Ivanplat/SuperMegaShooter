// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_MainUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_MainUIWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* I_Crosshair;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCPP_WeaponPanelWidget* WeaponPanelWidget;
};
