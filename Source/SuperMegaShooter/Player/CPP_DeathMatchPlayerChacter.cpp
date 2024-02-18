// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_DeathMatchPlayerChacter.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"

ACPP_DeathMatchPlayerChacter::ACPP_DeathMatchPlayerChacter()
{
	GetInventoryComponent()->SetShouldDestroyWeapons(true);
}
