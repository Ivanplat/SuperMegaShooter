// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponents/Character/CPP_BaseHealthComponent.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Net/UnrealNetwork.h"
#include "Base/Game/CPP_BaseGameMode.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "Player/CPP_PlayerCharacter.h"
#include "Player/CPP_PlayerState.h"
#include "Player/CPP_PlayerController.h"


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

inline int32 UCPP_BaseHealthComponent::GetHealth() const
{
	return Health;
}
