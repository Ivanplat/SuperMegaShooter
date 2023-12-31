// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerCharacter.h"
#include "Player/ActorComponents/CPP_PlayerHealthComponent.h"

ACPP_PlayerCharacter::ACPP_PlayerCharacter()
{
	HealthComponent = CreateDefaultSubobject<UCPP_PlayerHealthComponent>(TEXT("HealthComponent"));

	check(HealthComponent);

	HealthComponent->SetIsReplicated(true);
}

void ACPP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ACPP_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ACPP_PlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ACPP_PlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ACPP_PlayerCharacter::Turn);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACPP_PlayerCharacter::StartJump);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Released, this, &ACPP_PlayerCharacter::StopJump);
}

void ACPP_PlayerCharacter::MoveForward(float Axis)
{
	if (Axis == 0.0f) return;

	FVector direction = GetActorForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPP_PlayerCharacter::MoveRight(float Axis)
{
	if (Axis == 0.0f) return;

	FVector direction = GetActorRightVector();

	AddMovementInput(direction, Axis);
}

void ACPP_PlayerCharacter::LookUp(float Axis)
{
	if (Axis == 0.0f) return;

	AddControllerPitchInput(Axis);
}

void ACPP_PlayerCharacter::Turn(float Axis)
{
	if (Axis == 0.0f) return;

	AddControllerYawInput(Axis);
}

void ACPP_PlayerCharacter::StartJump()
{
	Jump();
}

void ACPP_PlayerCharacter::StopJump()
{
	StopJumping();
}
