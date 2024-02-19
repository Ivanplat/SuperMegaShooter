// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "CPP_PlayerCharacter.generated.h"

UCLASS()
class SUPERMEGASHOOTER_API ACPP_PlayerCharacter : public ACPP_BaseCharacter
{
	GENERATED_BODY()

public:
	ACPP_PlayerCharacter();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void MoveForward(float Axis);

	virtual void MoveRight(float Axis);

	virtual void LookUp(float Axis);

	virtual void Turn(float Axis);

	virtual void StartJump();

	virtual void StopJump();

	virtual void ScrollUp();

	virtual void ScrollDown();

	virtual void ShowTabStats();

	virtual void HideTabStats();

	UFUNCTION(Server, Reliable)
	void ServerUseWeapon();

	virtual void ServerUseWeapon_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerStopUsingWeapon();

	virtual void ServerStopUsingWeapon_Implementation();

	virtual void PossessedBy(AController* NewController) override;

};
