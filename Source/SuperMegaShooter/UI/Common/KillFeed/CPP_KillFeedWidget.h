// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_KillFeedWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_KillFeedWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void AddKillFeedMessage(class UCPP_KillFeedMessageWidget* WidgetToAdd);

protected:
	UFUNCTION()
	virtual void RemoveFirstKillFeedMessage();

protected:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VB_KillFeed;

	TQueue<class UCPP_KillFeedMessageWidget*> KillFeedQueue;

	UPROPERTY(EditDefaultsOnly, Category = "Kill Feed Widget")
	float RemovingFromKillFeedDelay = 1.0f;
};
