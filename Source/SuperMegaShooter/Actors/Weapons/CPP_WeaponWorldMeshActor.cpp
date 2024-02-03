// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/CPP_WeaponWorldMeshActor.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "CPP_WeaponComponent.h"

ACPP_WeaponWorldMeshActor::ACPP_WeaponWorldMeshActor()
{
	CREATE_WEAPON_COMPONENT(WeaponComponent);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));

	check(WeaponCollision);

	WeaponCollision->SetupAttachment(RootComponent);

	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	WeaponCollision->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	GetStaticMeshComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetStaticMeshComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    GetStaticMeshComponent()->SetSimulatePhysics(false);
	GetStaticMeshComponent()->SetIsReplicated(true);
}

void ACPP_WeaponWorldMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ACPP_BaseStaticMeshActor::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_WeaponWorldMeshActor, WeaponInfo);
}

void ACPP_WeaponWorldMeshActor::Interact_Implementation(ACPP_BaseCharacter* Caller)
{
	WeaponClass.LoadSynchronous();

	if (!WeaponClass.IsValid()) return;

	if (ACPP_Weapon* weapon = 
		GetWorld()->SpawnActor<ACPP_Weapon>(WeaponClass.Get()))
	{
		ICPP_WeaponInterface::Execute_MoveCommonWeaponInfo(weapon, WeaponInfo);
		weapon->MoveWeaponSkin(GetStaticMeshComponent()->GetMaterials());
		weapon->GetWeaponComponent()->OnWeaponMaterialsChanged();

		Caller->GetInventoryComponent()->PickUpWeapon(weapon);
	}

	WeaponClass.Reset();

	Destroy();
}

void ACPP_WeaponWorldMeshActor::MoveCommonWeaponInfo_Implementation(const FWeaponInfo& InWeaponInfo)
{
	WeaponInfo = InWeaponInfo;
}

void ACPP_WeaponWorldMeshActor::SetWeaponStaticMesh_Implementation(UStaticMesh* NewStaticMesh)
{
	GetStaticMeshComponent()->SetStaticMesh(NewStaticMesh);
	SetWeaponMeshSimulatePhysics(true);
}
