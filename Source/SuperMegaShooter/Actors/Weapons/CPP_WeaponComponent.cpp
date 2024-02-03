// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/CPP_WeaponComponent.h"
#include "CPP_Weapon.h"
#include "CPP_WeaponWorldMeshActor.h"
#include "Net/UnrealNetwork.h"

UCPP_WeaponComponent::UCPP_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCPP_WeaponComponent::OnWeaponMaterialsChanged()
{
	const int32 materialsCount = WeaponMaterials.Num();

	if (ACPP_Weapon* weapon = GetOwner<ACPP_Weapon>())
	{
		for (int32 i = 0; i < materialsCount; ++i)
		{
			weapon->GetSkeletalMeshComponent()->SetMaterial(i, WeaponMaterials[i]);
		}
	}
	else if (ACPP_WeaponWorldMeshActor* weaponMesh = GetOwner<ACPP_WeaponWorldMeshActor>())
	{
		for (int32 i = 0; i < materialsCount; ++i)
		{
			weaponMesh->GetStaticMeshComponent()->SetMaterial(i, WeaponMaterials[i]);
		}
	}
}

void UCPP_WeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCPP_WeaponComponent, WeaponMaterials);
}

