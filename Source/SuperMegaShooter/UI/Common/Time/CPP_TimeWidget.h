// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_TimeWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_TimeWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateTimeText(FText& OutValue);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Time;
};
