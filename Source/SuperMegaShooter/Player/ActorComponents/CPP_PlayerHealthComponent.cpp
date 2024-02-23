// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponents/CPP_PlayerHealthComponent.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/CPP_PlayerState.h"
#include "Player/CPP_PlayerController.h"
#include "Player/ActorComponents/CPP_PlayerInventoryComponent.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "Base/Game/CPP_BaseGameMode.h"

bool UCPP_PlayerHealthComponent::ApplyDamage(AActor* Instigator, AActor* DamageCauser, const FName& HittedBoneName)
{
	if (!bAlive) return false;

	if (ACPP_Weapon* weapon = Cast<ACPP_Weapon>(DamageCauser))
	{

		int32 baseDamge = weapon->GetWeaponDamage();

		if (HittedBoneName != NAME_None)
		{
			baseDamge = RecalculateDamage(baseDamge, HittedBoneName);
		}

		Health -= baseDamge;

		if (Health <= 0)
		{
			bAlive = false;

			GetComponentOwner<ACPP_PlayerCharacter>()->GetPlayerState<ACPP_PlayerState>()->PlayerDeadDelegate.Broadcast();

			if (ACPP_PlayerController* instigatorController = Cast<ACPP_PlayerController>(Instigator))
			{
				instigatorController->GetPlayerState<ACPP_PlayerState>()->PlayerKilledDelegate.Broadcast();
			}

			GetComponentOwner()->GetController<ACPP_PlayerController>()
					->PlayerDeadDelegate.Broadcast
					(
						Cast<AController>(Instigator)->GetPlayerState<APlayerState>()->GetPlayerName(),
						GetComponentOwner()->GetPlayerState<APlayerState>()->GetPlayerName(),
						Cast<ACPP_Weapon>(DamageCauser)->WeaponInfo.WeaponUIKillFeedTexture
					);


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
