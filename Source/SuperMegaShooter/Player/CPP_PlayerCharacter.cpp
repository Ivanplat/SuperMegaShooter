// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerCharacter.h"
#include "Player/ActorComponents/CPP_PlayerHealthComponent.h"
#include "Player/ActorComponents/CPP_PlayerInventoryComponent.h"
#include "Actors/Weapons/CPP_Weapon.h"

ACPP_PlayerCharacter::ACPP_PlayerCharacter()
{
	HealthComponent = CreateDefaultSubobject<UCPP_PlayerHealthComponent>(TEXT("HealthComponent"));
	InventoryComponent = CreateDefaultSubobject<UCPP_PlayerInventoryComponent>(TEXT("InventoryComponent"));

	check(HealthComponent);
	check(InventoryComponent);

	HealthComponent->SetIsReplicated(true);
	InventoryComponent->SetIsReplicated(true);
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
	PlayerInputComponent->BindAction(FName("Interact"), IE_Pressed, this, &ACPP_PlayerCharacter::ServerInteract);
	PlayerInputComponent->BindAction(FName("DropWeapon"), IE_Pressed, this, &ACPP_PlayerCharacter::ServerDropWeapon);
	PlayerInputComponent->BindAction(FName("UseWeapon"), IE_Pressed, this, &ACPP_PlayerCharacter::ServerUseWeapon);
	PlayerInputComponent->BindAction(FName("UseWeapon"), IE_Released, this, &ACPP_PlayerCharacter::ServerStopUsingWeapon);
	PlayerInputComponent->BindAction(FName("Reload"), IE_Pressed, this, &ACPP_PlayerCharacter::ServerReloadWeapon);
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

void ACPP_PlayerCharacter::ServerUseWeapon_Implementation()
{
	if (ACPP_Weapon* selectedWeapon = GetInventoryComponent()->GetSelectedWeapon())
	{
		selectedWeapon->UseWeapon();
	}
}

void ACPP_PlayerCharacter::ServerStopUsingWeapon_Implementation()
{
	if (ACPP_Weapon* selectedWeapon = GetInventoryComponent()->GetSelectedWeapon())
	{
		selectedWeapon->StopUsingWeapon();
	}
}
