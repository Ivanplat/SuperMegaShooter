// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ActorComponents/Character/CPP_BaseCharacterComponent.h"
#include "Base/CPP_BaseCharacter.h"

UCPP_BaseCharacterComponent::UCPP_BaseCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

inline ACPP_BaseCharacter* UCPP_BaseCharacterComponent::GetComponentOwner() const
{
	return ComponentOwner;
}


void UCPP_BaseCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
	
	ComponentOwner = GetOwner<ACPP_BaseCharacter>();
}