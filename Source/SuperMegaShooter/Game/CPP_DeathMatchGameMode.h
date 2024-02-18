// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "CPP_DeathMatchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_DeathMatchGameMode : public ACPP_BaseGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
