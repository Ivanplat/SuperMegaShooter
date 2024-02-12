// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerCharacter.h"
#include "Player/ActorComponents/CPP_PlayerHealthComponent.h"
#include "Player/ActorComponents/CPP_PlayerInventoryComponent.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "CPP_PlayerController.h"

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
	PlayerInputComponent->BindAction(FName("Crouch"), IE_Pressed, this, &ACPP_PlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction(FName("Crouch"), IE_Released, this, &ACPP_PlayerCharacter::StopCrouching);
	PlayerInputComponent->BindAction(FName("SelectMainWeapon"), IE_Pressed, this, &ACPP_PlayerCharacter::SelectMainWeapon);
	PlayerInputComponent->BindAction(FName("SelectSecondaryWeapon"), IE_Pressed, this, &ACPP_PlayerCharacter::SelectSecondaryWeapon);
	PlayerInputComponent->BindAction(FName("SelectMeleeWeapon"), IE_Pressed, this, &ACPP_PlayerCharacter::SelectMeleeWeapon);
	PlayerInputComponent->BindAction(FName("ScrollUp"), IE_Pressed, this, &ACPP_PlayerCharacter::ScrollUp);
	PlayerInputComponent->BindAction(FName("ScrollDown"), IE_Pressed, this, &ACPP_PlayerCharacter::ScrollDown);
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

void ACPP_PlayerCharacter::ScrollUp()
{
	if (ACPP_Weapon* selectedWeapon = GetInventoryComponent()->GetSelectedWeapon())
	{
		const EWeaponType selectedWeaponType = selectedWeapon->WeaponInfo.WeaponType;

		EWeaponType nextWeaponType = EWeaponType::WT_MainWeapon;

		switch (selectedWeaponType)
		{
		case EWeaponType::WT_MainWeapon:	  nextWeaponType = EWeaponType::WT_MeleeWeapon;     break;
		case EWeaponType::WT_SecondaryWeapon: nextWeaponType = EWeaponType::WT_MainWeapon;      break;
		case EWeaponType::WT_MeleeWeapon:	  nextWeaponType = EWeaponType::WT_SecondaryWeapon; break;
		}

		GetInventoryComponent()->SelectWeaponByWeaponType(nextWeaponType);
	}
}

void ACPP_PlayerCharacter::ScrollDown()
{
	if (ACPP_Weapon* selectedWeapon = GetInventoryComponent()->GetSelectedWeapon())
	{
		const EWeaponType selectedWeaponType = selectedWeapon->WeaponInfo.WeaponType;

		EWeaponType prevWeaponType = EWeaponType::WT_MainWeapon;

		switch (selectedWeaponType)
		{
		case EWeaponType::WT_MainWeapon:	  prevWeaponType = EWeaponType::WT_SecondaryWeapon; break;
		case EWeaponType::WT_SecondaryWeapon: prevWeaponType = EWeaponType::WT_MeleeWeapon;     break;
		case EWeaponType::WT_MeleeWeapon:	  prevWeaponType = EWeaponType::WT_MainWeapon;      break;
		}

		GetInventoryComponent()->SelectWeaponByWeaponType(prevWeaponType);
	}
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

void ACPP_PlayerCharacter::PossessedBy(AController* NewController)
{
	ACPP_BaseCharacter::PossessedBy(NewController);

	FTimerHandle th;
	FTimerDelegate td;

	td.BindUFunction(GetController<ACPP_PlayerController>(), FName("ClientCallCharacterReadyDelegate"));

	GetWorld()->GetTimerManager().SetTimer(th, td, 0.3f, false, 0.3f);
}
