// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_TabStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_TabStatsWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VB_Players;

	UPROPERTY(EditDefaultsOnly, Category = "Tab Stats Widget | Classes")
	TSoftClassPtr<class UCPP_TabPlayerStatsWidget> TabPlayerStatsWidgetClassPtr;
};
