// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "Interfaces/CPP_InteractionInterface.h"
#include "CPP_BaseSkeletalMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_BaseSkeletalMeshActor : public ASkeletalMeshActor, public ICPP_InteractionInterface
{
	GENERATED_BODY()
	
public:
	ACPP_BaseSkeletalMeshActor();
};
