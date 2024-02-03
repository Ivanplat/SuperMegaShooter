// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponents/Character/CPP_BaseHealthComponent.h"
#include "Base/Character/CPP_BaseCharacter.h"

#include "Net/UnrealNetwork.h"


void UCPP_BaseHealthComponent::BeginPlay()
{
	UCPP_BaseCharacterComponent::BeginPlay();
}

void UCPP_BaseHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UCPP_BaseCharacterComponent::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCPP_BaseHealthComponent, Health);
}

bool UCPP_BaseHealthComponent::ApplyDamage(AActor* Instigator, AActor* Weapon)
{
	return true;
}
