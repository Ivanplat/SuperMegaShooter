// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Character/CPP_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/CPP_InteractionInterface.h"
#include "DrawDebugHelpers.h"
#include "Base/ActorComponents/Character/CPP_BaseInventoryComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void ACPP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		FTimerHandle th;
		FTimerDelegate td;

		td.BindUObject(GetInventoryComponent(), &UCPP_BaseInventoryComponent::SpawnInitialWeaponsSet);

		GetWorld()->GetTimerManager().SetTimer(th, td, 0.5f, false, 0.5f);
	}
}

void ACPP_BaseCharacter::ServerDropWeapon_Implementation()
{
	UCPP_BaseInventoryComponent* inventory = GetInventoryComponent();
	inventory->DropWeapon(inventory->GetSelectedWeapon());
}

void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

inline USkeletalMeshComponent* ACPP_BaseCharacter::GetVisibleMesh() const
{
	return IsLocallyControlled() ? FPMesh : GetMesh();
}

inline USkeletalMeshComponent* ACPP_BaseCharacter::GetFPMesh() const
{
	return FPMesh;
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
