// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Game/CPP_BaseGameState.h"
#include "Net/UnrealNetwork.h"
#include "Base/Game/CPP_BaseGameMode.h"


void ACPP_BaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_BaseGameState, Seconds);
	DOREPLIFETIME(ACPP_BaseGameState, Minutes);
}

inline int32 ACPP_BaseGameState::GetSeconds() const
{
	return Seconds;
}

inline int32 ACPP_BaseGameState::GetMinutes() const
{
	return Minutes;
}

void ACPP_BaseGameState::OnGameStarted()
{
	FTimerDelegate td;

	td.BindUFunction(this, FName("UpdateRoundTime"));

	GetWorld()->GetTimerManager().SetTimer(UpdateRoundTimeTimerHandle, td, 1.0f, true, 1.0f);
}

void ACPP_BaseGameState::OnGameOver()
{
	if (UpdateRoundTimeTimerHandle.IsValid() && GetWorld()->GetTimerManager().IsTimerActive(UpdateRoundTimeTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateRoundTimeTimerHandle);
	}
}

void ACPP_BaseGameState::UpdateRoundTime()
{
	if (Minutes == 0 && Seconds == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateRoundTimeTimerHandle);
		GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>()->GameOverDelegate.Broadcast();
		return;
	}

	if (Seconds > 0)
	{
		--Seconds;
	}
	else
	{
		Seconds = 59;
		--Minutes;
	}
}

void ACPP_BaseGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>()->GameStartedDelegate.AddDynamic(this, &ACPP_BaseGameState::OnGameStarted);
		GetWorld()->GetAuthGameMode<ACPP_BaseGameMode>()->GameOverDelegate.AddDynamic(this, &ACPP_BaseGameState::OnGameOver);
	}
}
