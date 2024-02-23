// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/CPP_PlayerController.h"
#include "CPP_TeamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_TeamPlayerController : public ACPP_PlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
