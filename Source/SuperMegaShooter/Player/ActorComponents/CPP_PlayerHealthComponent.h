// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/ActorComponents/Character/CPP_BaseHealthComponent.h"
#include "CPP_PlayerHealthComponent.generated.h"

UCLASS()
class SUPERMEGASHOOTER_API UCPP_PlayerHealthComponent : public UCPP_BaseHealthComponent
{
	GENERATED_BODY()
	
public:
	virtual bool ApplyDamage(AActor* Instigator, AActor* DamageCauser) override;
};
