// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Actors/CPP_BaseStaticMeshActor.h"

ACPP_BaseStaticMeshActor::ACPP_BaseStaticMeshActor()
{
	bReplicates = true;
	bStaticMeshReplicateMovement = true;
	SetReplicateMovement(true);
}
