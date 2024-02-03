// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/CPP_WeaponInterface.h"
#include "Actors/Weapons/CPP_Weapon.h"
#include "Actors/Weapons/CPP_WeaponWorldMeshActor.h"
#include "Actors/Weapons/CPP_WeaponComponent.h"

inline UCPP_WeaponComponent* ICPP_WeaponInterface::GetWeaponComponent() const
{
    UCPP_WeaponComponent* weaponComponent = nullptr;

    if (const ACPP_Weapon* weapon = Cast<ACPP_Weapon>(this))
    {
        weaponComponent = weapon->WeaponComponent;
    }
    else if (const ACPP_WeaponWorldMeshActor* weaponMeshActor = Cast<ACPP_WeaponWorldMeshActor>(this))
    {
        weaponComponent = weaponMeshActor->WeaponComponent;
    }

    return weaponComponent;
}

void ICPP_WeaponInterface::MoveWeaponSkin(const TArray<UMaterialInterface*>& InWeaponMaterials)
{
    int32 materialsCount = 0;

    if (const ACPP_Weapon* weapon = Cast<ACPP_Weapon>(this))
    {
        materialsCount = weapon->GetSkeletalMeshComponent()->GetNumMaterials();
    }
    else if (const ACPP_WeaponWorldMeshActor* weaponMeshActor = Cast<ACPP_WeaponWorldMeshActor>(this))
    {
        materialsCount = weaponMeshActor->GetStaticMeshComponent()->GetNumMaterials();
    }

    const int32 inMaterialsCount = InWeaponMaterials.Num();

    if (materialsCount != inMaterialsCount) return;

    GetWeaponComponent()->WeaponMaterials = InWeaponMaterials;
}
