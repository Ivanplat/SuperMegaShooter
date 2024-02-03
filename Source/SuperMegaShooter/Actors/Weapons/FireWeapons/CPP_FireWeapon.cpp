// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/FireWeapons/CPP_FireWeapon.h"
#include "Net/UnrealNetwork.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void ACPP_FireWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ACPP_Weapon::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_FireWeapon, CurrentAmmo);
	DOREPLIFETIME(ACPP_FireWeapon, CurrentAmmoInBack);
	DOREPLIFETIME(ACPP_FireWeapon, MaxCurrentAmmo);
	DOREPLIFETIME(ACPP_FireWeapon, MaxAmmoInBack);
}

void ACPP_FireWeapon::UseWeapon()
{
	TryUseWeapon();
}

void ACPP_FireWeapon::StopUsingWeapon()
{
	ACPP_Weapon::StopUsingWeapon();

	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimeHandler);
}

bool ACPP_FireWeapon::TryUseWeapon()
{
	if (AbleToUseWeapon())
	{
		bWeaponInUse = true;
		Fire();
		return true;
	}
	return false;
}

bool ACPP_FireWeapon::AbleToUseWeapon()
{
	return !bWeaponInUse && CurrentAmmo > 0;
}

void ACPP_FireWeapon::Fire()
{
	if (!WeaponOwner) return;

	FVector start, end, temp;
	FRotator rotator;
	FHitResult hitResult;
	FCollisionQueryParams params;

	params.AddIgnoredActor(WeaponOwner);
	params.AddIgnoredActor(this);
	
	WeaponOwner->GetActorEyesViewPoint(start, rotator);

	end = start + rotator.Vector() * 10000.0f;

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, (uint8)0U, 0.5f);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params))
	{
		if (AActor* hittedActor = hitResult.GetActor())
		{
			UGameplayStatics::ApplyPointDamage
			(
				hittedActor,
				static_cast<float>(Damage),
				UKismetMathLibrary::GetDirectionUnitVector(start, end),
				hitResult,
				WeaponOwner->GetController(),
				this,
				WeaponDamageType
			);
		}
	}

	DecreaseAmmo();

	if (bAbleToAutoFire && CurrentAmmo > 0)
	{
		FTimerDelegate td;

		td.BindUObject(this, &ACPP_FireWeapon::Fire);

		GetWorld()->GetTimerManager().SetTimer(AutoFireTimeHandler, td, FireDelay, false, FireDelay);
	}
}

void ACPP_FireWeapon::DecreaseAmmo()
{
	if (CurrentAmmo > 0) --CurrentAmmo;

	if (CurrentAmmo == 0)
	{
		StopUsingWeapon();
	}
}

void ACPP_FireWeapon::PlayWeaponAnimationMulticast_Implementation(EWeaponAnimationType AnimationType)
{
	UAnimationAsset* animation = nullptr;

	switch (AnimationType)
	{
	case EWeaponAnimationType::WAnT_Idle:		animation = IdleAnimation;		 break;
	case EWeaponAnimationType::WAnT_Using:      animation = UsingAnimation;		 break;
	case EWeaponAnimationType::WAnT_Reloading:  animation = ReloadingAnimation;  break;
	case EWeaponAnimationType::WAnT_Inspection: animation = InspectionAnimation; break;
	}

	if (animation)
	{
		GetSkeletalMeshComponent()->PlayAnimation(animation, false);
	}
}
