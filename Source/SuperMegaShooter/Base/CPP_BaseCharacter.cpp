// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/CPP_BaseCharacter.h"
#include "Camera/CameraComponent.h"

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
	
}

void ACPP_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

inline USkeletalMeshComponent* ACPP_BaseCharacter::GetVisibleMesh() const
{
	return IsLocallyControlled() ? FPMesh : GetMesh();
}

inline UCPP_BaseHealthComponent* ACPP_BaseCharacter::GetHealthComponent() const
{
	return HealthComponent;
}
