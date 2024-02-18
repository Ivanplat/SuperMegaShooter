// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Player/CPP_PlayerController.h"
#include "Base/UI/CPP_BaseHUD.h"

ACPP_PlayerState::ACPP_PlayerState()
{
	PlayerKilledDelegate.AddDynamic(this, &ACPP_PlayerState::OnPlayerKilled);
	PlayerDeadDelegate.AddDynamic(this, &ACPP_PlayerState::OnPlayerDead);
}

void ACPP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_PlayerState, Kills);
	DOREPLIFETIME(ACPP_PlayerState, Deaths);
}

inline int32 ACPP_PlayerState::GetKills() const
{
	return Kills;
}

inline int32 ACPP_PlayerState::GetDeaths() const
{
	return Deaths;
}

void ACPP_PlayerState::OnPlayerKilled()
{
	++Kills;
}

void ACPP_PlayerState::OnPlayerDead()
{
	++Deaths;
}

void ACPP_PlayerState::ClientNotifyKillFeed_Implementation(const FString& KillerName, const FString& VictimName, UTexture2D* DeathCauserUITexture)
{
	Cast<ACPP_PlayerController>(GetOwningController())->GetHUD<ACPP_BaseHUD>()->AddKillFeedMessage(KillerName, VictimName, DeathCauserUITexture);
}
