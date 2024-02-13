// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/CPP_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/CPP_InteractionInterface.h"
#include "DrawDebugHelpers.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterWeaponAnimationInfo.h"
#include "Actors/Weapons/FireWeapons/CPP_FireWeapon.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetMathLibrary.h"
#include "Base/ActorComponents/Character/CPP_BaseHealthComponent.h"

ACPP_BaseCharacter::ACPP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));

	check(FPCamera);
	check(FPMesh);

	FPCamera->SetupAttachment(RootComponent);
	FPMesh->SetupAttachment(FPCamera);

	FPCamera->bUsePawnControlRotation = true;

	GetMesh()->bOwnerNoSee = true;
	FPMesh->bOnlyOwnerSee = true;
	FPMesh->CastShadow = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> characterWeaponAnimsHelper(TEXT("/Script/Engine.DataTable'/Game/Blueprints/Character/DT_CharacterWeaponsAnimations.DT_CharacterWeaponsAnimations'"));

	if (characterWeaponAnimsHelper.Succeeded())
	{
		CharacterWeaponAnimationsDataTable = characterWeaponAnimsHelper.Object;
	}

	GetMovementComponent()->NavAgentProps.bCanCrouch = true;


	OnTakePointDamage.AddDynamic(this, &ACPP_BaseCharacter::OnCharacterTakePointDamage);
}

void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_BaseCharacter::ServerDropWeapon_Implementation()
{
	UCPP_BaseInventoryComponent* inventory = GetInventoryComponent();
	inventory->DropWeapon(inventory->GetSelectedWeapon());
}

void ACPP_BaseCharacter::MulticastPlayCharaterWeaponMontage_Implementation(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float NeededTime)
{
	if (!CharacterWeaponAnimationsDataTable) return;

	FString context;
	FName rowName;

	FCharacterWeaponAnimationInfoMap::GetRowNameByWeaponId(rowName, WeaponId);

	if (
		FCharacterWeaponAnimationInfoMap* row = CharacterWeaponAnimationsDataTable->
		FindRow<FCharacterWeaponAnimationInfoMap>(rowName, context)
		)
	{
		FName animationTypeName;

		FCharacterWeaponAnimationInfo::GetAnimationNameByType(animationTypeName, AnimationType);

		if (UAnimMontage** montage = row->CharacterWeaponMontages.CharacterWeaponMontage.Find(animationTypeName))
		{
			if (UAnimInstance* animInstance = GetVisibleMesh()->GetAnimInstance())
			{
				float playRate = 1.0f;

				if (NeededTime > 0.0f)
				{
					float timeEx = (*montage)->GetPlayLength();
					playRate = timeEx / NeededTime;
				}

				animInstance->Montage_Play(*montage, playRate);
			}
		}
	}
}

void ACPP_BaseCharacter::MulticastStopPlayCharacterWeaponMontage_Implementation(EWeaponId WeaponId, EWeaponAnimationType AnimationType, float BlendTime)
{
	if (!CharacterWeaponAnimationsDataTable) return;

	FString context;
	FName rowName;

	FCharacterWeaponAnimationInfoMap::GetRowNameByWeaponId(rowName, WeaponId);

	if (
		FCharacterWeaponAnimationInfoMap* row = CharacterWeaponAnimationsDataTable->
		FindRow<FCharacterWeaponAnimationInfoMap>(rowName, context)
		)
	{
		FName animationTypeName;

		FCharacterWeaponAnimationInfo::GetAnimationNameByType(animationTypeName, AnimationType);

		if (UAnimMontage** montage = row->CharacterWeaponMontages.CharacterWeaponMontage.Find(animationTypeName))
		{
			if (UAnimInstance* animInstance = GetVisibleMesh()->GetAnimInstance())
			{
				animInstance->Montage_Stop(BlendTime, *montage);
			}
		}
	}
}

void ACPP_BaseCharacter::ServerReloadWeapon_Implementation()
{
	if (ACPP_FireWeapon* fireWeapon = Cast<ACPP_FireWeapon>(GetInventoryComponent()->GetSelectedWeapon()))
	{
		fireWeapon->Reload();
	}
}

void ACPP_BaseCharacter::StartCrouch()
{
	Crouch();
}

void ACPP_BaseCharacter::StopCrouching()
{
	UnCrouch();
}

void ACPP_BaseCharacter::SelectMainWeapon()
{
	GetInventoryComponent()->SelectWeaponByWeaponType(EWeaponType::WT_MainWeapon);
}

void ACPP_BaseCharacter::SelectSecondaryWeapon()
{
	GetInventoryComponent()->SelectWeaponByWeaponType(EWeaponType::WT_SecondaryWeapon);
}

void ACPP_BaseCharacter::SelectMeleeWeapon()
{
	GetInventoryComponent()->SelectWeaponByWeaponType(EWeaponType::WT_MeleeWeapon);
}

inline void ACPP_BaseCharacter::CalculateLookingVerticalAngle()
{
	if (AActor* controller = Cast<AActor>(GetController()))
	{
		LookingVerticalAngle = UKismetMathLibrary::Conv_VectorToRotator(controller->GetActorForwardVector()).Pitch;
	}
}

void ACPP_BaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController)
	{
		FTimerHandle th;
		FTimerDelegate td;

		td.BindUObject(GetInventoryComponent(), &UCPP_BaseInventoryComponent::SpawnInitialWeaponsSet);

		GetWorld()->GetTimerManager().SetTimer(th, td, 0.5f, false, 0.5f);
	}
}

void ACPP_BaseCharacter::OnCharacterTakePointDamage
(
	AActor* DamagedActor,
	float Damage,
	AController* InstigatedBy,
	FVector HitLocation, 
	UPrimitiveComponent* HitComponent, 
	FName BoneName,
	FVector ShotDirectionFrom, 
	const UDamageType* DamageType,
	AActor* DamageCauser
)
{
	if (HasAuthority())
	{
		GetHealthComponent()->ApplyDamage(InstigatedBy, DamageCauser);
	}
}

void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateLookingVerticalAngle();
}

inline USkeletalMeshComponent* ACPP_BaseCharacter::GetVisibleMesh() const
{
	return IsLocallyControlled() ? FPMesh : GetMesh();
}

inline USkeletalMeshComponent* ACPP_BaseCharacter::GetFPMesh() const
{
	return FPMesh;
}

inline UCameraComponent* ACPP_BaseCharacter::GetFPCamera() const
{
	return FPCamera;
}

inline bool ACPP_BaseCharacter::TryGetCharacterLookingVector(FVector& OutVector) const
{
	if (AController* controller = GetController())
	{
		FVector headLocation, endLocation;
		FRotator rotator;

		controller->GetActorEyesViewPoint(headLocation, rotator);
		endLocation = headLocation + rotator.Vector()*2.0f;

		OutVector = UKismetMathLibrary::GetDirectionUnitVector(headLocation, endLocation);

		return true;
	}
	return false;
}

void ACPP_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_BaseCharacter, LookingVerticalAngle);
}

void ACPP_BaseCharacter::ServerInteract_Implementation()
{
	const float distance = 300.0f;
	FHitResult hitResult;
	FVector start, end, temp;
	FRotator rotator;
	FCollisionQueryParams params;

	params.AddIgnoredActor(this);

	GetController()->GetActorEyesViewPoint(temp, rotator);

	start = FPCamera->GetComponentLocation();
	end = start + rotator.Vector() * distance;

	GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility, params);

	if (AActor* actor = hitResult.GetActor())
	{
		if (actor->Implements<UCPP_InteractionInterface>())
		{
			ICPP_InteractionInterface::Execute_Interact(actor, this);
		}
	}

}

inline UCPP_BaseInventoryComponent* ACPP_BaseCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

inline UCPP_BaseHealthComponent* ACPP_BaseCharacter::GetHealthComponent() const
{
	return HealthComponent;
}
