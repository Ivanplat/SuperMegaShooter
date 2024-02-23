// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/FireWeapons/CPP_FireWeapon.h"
#include "Net/UnrealNetwork.h"
#include "Base/Character/CPP_BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Base/Game/CPP_BaseGameMode.h"

ACPP_FireWeapon::ACPP_FireWeapon()
{
	GunFirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("GunFirePoint"));

	check(GunFirePoint);

	GunFirePoint->SetupAttachment(GetSkeletalMeshComponent());

	WeaponSounds.Add(TPair<FName, USoundBase*>
		(
			FName("Reloading"), static_cast<USoundBase*>(nullptr)
		));

	RecoilReseterTimerDelegate.BindUFunction(this, FName("ResetRecoil"));
}

void ACPP_FireWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ACPP_Weapon::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_FireWeapon, CurrentAmmo);
	DOREPLIFETIME(ACPP_FireWeapon, CurrentAmmoInBack);
	DOREPLIFETIME(ACPP_FireWeapon, MaxCurrentAmmo);
	DOREPLIFETIME(ACPP_FireWeapon, MaxAmmoInBack);
	DOREPLIFETIME(ACPP_FireWeapon, bReloading);
}

void ACPP_FireWeapon::UseWeapon()
{
	TryUseWeapon();
}

void ACPP_FireWeapon::StopUsingWeapon()
{
	ACPP_Weapon::StopUsingWeapon();

	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimeHandler);
	GetWorld()->GetTimerManager().SetTimer(RecoilReseterTimerHandler, RecoilReseterTimerDelegate, 0.5f, true, 0.5f);
}

bool ACPP_FireWeapon::TryUseWeapon()
{
	if (IsAbleToUseWeapon())
	{
		bWeaponInUse = true;
		Fire();
		return true;
	}
	return false;
}

bool ACPP_FireWeapon::IsAbleToUseWeapon() const
{
	return !bWeaponInUse && CurrentAmmo > 0 && !bReloading && !bWeaponLocked;
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
	
	WeaponOwner->GetActorEyesViewPoint(temp, rotator);

	start = WeaponOwner->GetFPCamera()->GetComponentLocation();
	end = start + rotator.Vector() * 10000.0f;

	//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, (uint8)0U, 0.5f);

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

	if (RecoilReseterTimerHandler.IsValid() && GetWorld()->GetTimerManager().IsTimerActive(RecoilReseterTimerHandler))
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoilReseterTimerHandler);
	}

	PlayWeaponSoundByType(EWeaponSoundType::WST_Using);
	PlayUsingWeaponEffects();
	AddRecoil();

	PlayWeaponAnimationMulticast(EWeaponAnimationType::WAnT_Using);
	WeaponOwner->MulticastPlayCharaterWeaponMontage(WeaponId, EWeaponAnimationType::WAnT_Using, FireDelay);


	if (ACPP_BaseGameMode* gameMode = GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>())
	{
		if (gameMode->GameModeAmmoSettings != EGameModeAmmoSettings::GMAS_InfinityAmmo1)
		{
			DecreaseAmmo();
		}
	}

	if (bAbleToAutoFire && CurrentAmmo > 0)
	{
		FTimerDelegate td;

		td.BindUObject(this, &ACPP_FireWeapon::Fire);

		GetWorld()->GetTimerManager().SetTimer(AutoFireTimeHandler, td, FireDelay, false, FireDelay);
	}

	if (IsNeededToReload())
	{
		StopUsingWeapon();

		Reload();
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

void ACPP_FireWeapon::AddRecoil()
{
	if (LastRecoilIndex < FireWeaponRecoil.Num() - 1)
	{
		WeaponOwner->ClientAddRecoil(FireWeaponRecoil[LastRecoilIndex++]);
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
	case EWeaponAnimationType::WAnT_Preparing:  animation = PreparingAnimation;  break;
	}

	if (animation)
	{
		GetSkeletalMeshComponent()->PlayAnimation(animation, false);
	}
}

bool ACPP_FireWeapon::IsAbleToReload() const
{
	return CurrentAmmo < MaxCurrentAmmo && CurrentAmmoInBack > 0 && !bReloading && !bWeaponInUse && !bWeaponLocked;
}

void ACPP_FireWeapon::Reload()
{
	if (IsAbleToReload())
	{
		bReloading = true;

		FTimerDelegate td;

		td.BindUFunction(this, FName("EndReloading"));

		GetWorld()->GetTimerManager().SetTimer(ReloadingTimerHandler, td, ReloadingTime, false, ReloadingTime);

		PlayWeaponSoundByType(EWeaponSoundType::WST_Reloading);
		PlayWeaponAnimationMulticast(EWeaponAnimationType::WAnT_Reloading);
		WeaponOwner->MulticastPlayCharaterWeaponMontage(WeaponId, EWeaponAnimationType::WAnT_Reloading, ReloadingTime);
	}
}

void ACPP_FireWeapon::ManualStopReloading()
{
	GetWorld()->GetTimerManager().ClearTimer(ReloadingTimerHandler);

	///

	StopPlayingAudioComponents();
	bReloading = false;
	WeaponOwner->MulticastStopPlayCharacterWeaponMontage(WeaponId, EWeaponAnimationType::WAnT_Reloading);
}

inline bool ACPP_FireWeapon::IsReloading() const
{
	return bReloading;
}

inline int32 ACPP_FireWeapon::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

inline int32 ACPP_FireWeapon::GetCurrentAmmoInBack() const
{
	return CurrentAmmoInBack;
}

void ACPP_FireWeapon::EndReloading()
{
	if (ACPP_BaseGameMode* gameMode = GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>())
	{
		if (gameMode->GameModeAmmoSettings == EGameModeAmmoSettings::GMAS_InfinityAmmo2)
		{
			CurrentAmmo = MaxCurrentAmmo;


			bReloading = false;

			if (RecoilReseterTimerHandler.IsValid() && GetWorld()->GetTimerManager().IsTimerActive(RecoilReseterTimerHandler))
			{
				GetWorld()->GetTimerManager().ClearTimer(RecoilReseterTimerHandler);
			}

			LastRecoilIndex = 0;

			return;
		}
	}


	const int32 ammoNeededToReload = MaxCurrentAmmo - CurrentAmmo;
	
	if (ammoNeededToReload <= CurrentAmmoInBack)
	{
		CurrentAmmo += ammoNeededToReload;
		CurrentAmmoInBack -= ammoNeededToReload;
	}
	else
	{
		CurrentAmmo += CurrentAmmoInBack;
		CurrentAmmoInBack = 0;
	}

	bReloading = false;

	if (RecoilReseterTimerHandler.IsValid() && GetWorld()->GetTimerManager().IsTimerActive(RecoilReseterTimerHandler))
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoilReseterTimerHandler);
	}

	LastRecoilIndex = 0;
}

bool ACPP_FireWeapon::IsNeededToReload() const
{
	return CurrentAmmo == 0;
}


void ACPP_FireWeapon::PlayUsingWeaponEffects_Implementation()
{
	if (UsingParticleSystemTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UsingParticleSystemTemplate, GunFirePoint->GetComponentTransform());
	}
}

void ACPP_FireWeapon::ResetRecoil()
{
	if (bWeaponInUse || LastRecoilIndex == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoilReseterTimerHandler);
		return;
	}

	LastRecoilIndex /= 2;
}
