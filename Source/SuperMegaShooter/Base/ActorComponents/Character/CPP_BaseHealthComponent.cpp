// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponents/Character/CPP_BaseHealthComponent.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Net/UnrealNetwork.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"


void UCPP_BaseHealthComponent::BeginPlay()
{
	UCPP_BaseCharacterComponent::BeginPlay();
}

void UCPP_BaseHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UCPP_BaseCharacterComponent::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCPP_BaseHealthComponent, Health);
	DOREPLIFETIME(UCPP_BaseHealthComponent, bAlive);
}

bool UCPP_BaseHealthComponent::ApplyDamage(AActor* Instigator, AActor* DamageCauser)
{
	if (!bAlive) return false;

	if (ACPP_Weapon* weapon = Cast<ACPP_Weapon>(DamageCauser))
	{
		Health -= weapon->GetWeaponDamage();

		UE_LOG(LogTemp, Error, TEXT("%i"), Health);

		if (Health <= 0)
		{
			bAlive = false;

			GetComponentOwner()->GetInventoryComponent()->OnCharacterDestroyed();

			GetWorld()->
				GetAuthGameMode<ACPP_BaseGameMode>()->
				CharacterDiedDelegate.
				Broadcast(GetOwner<ACPP_BaseCharacter>()->GetController());
		}

		return true;
	}

	return false;
}
