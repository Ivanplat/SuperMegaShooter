// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_KillFeedMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_KillFeedMessageWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()
	
public:
	inline UCPP_KillFeedMessageWidget* SetKillerNickname(FText NewName);

	inline UCPP_KillFeedMessageWidget* SetVictimNickname(FText NewName);

	inline UCPP_KillFeedMessageWidget* SetWeponImageTexture(UTexture2D* NewImageTexture);

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyKillFeedMessage();

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KillerNickname;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* VictimNickname;

	UPROPERTY(meta = (BindWidget))
	class UImage* I_WeaponImage;
};
