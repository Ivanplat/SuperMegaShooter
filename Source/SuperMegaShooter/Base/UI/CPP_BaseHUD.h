// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPP_BaseHUD.generated.h"

UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPlayerCharacterReady() {}

	UFUNCTION()
	virtual void OnPlayerCharacterDead() {}
};
