// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPP_TeamGameState.h"
#include "Net/UnrealNetwork.h"
#include "Player/CPP_TeamPlayerController.h"
#include "GameFramework/PlayerState.h"

inline void ACPP_TeamGameState::GetTeam1(TArray<class ACPP_TeamPlayerController*>& OutValue) const
{
	OutValue = Team1;
}

inline void ACPP_TeamGameState::GetTeam2(TArray<class ACPP_TeamPlayerController*>& OutValue) const
{
	OutValue = Team2;
}

void ACPP_TeamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	ACPP_BaseGameState::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_TeamGameState, Team1);
	DOREPLIFETIME(ACPP_TeamGameState, Team2);
}

void ACPP_TeamGameState::BeginPlay()
{
	ACPP_BaseGameState::BeginPlay();


}

void ACPP_TeamGameState::ServerChangeTeam_Implementation(ACPP_TeamPlayerController* PlayerController, int32 TeamIndex)
{
	FUniqueNetIdRepl netId = PlayerController->GetPlayerState<APlayerState>()->BP_GetUniqueId();

	if (TeamIndex == 0)
	{
		if (Team1.Num() > 4)
		{
			return;
		}

		if (Team1.FindByPredicate(
			[=](ACPP_TeamPlayerController* PlayerContoller)->bool 
			{
				return PlayerContoller->GetPlayerState<APlayerState>()->GetUniqueId() == netId;
			}) != nullptr)
		{
			return;
		}

		if (ACPP_TeamPlayerController** playerControllerPtr = Team2.FindByPredicate(
			[=](ACPP_TeamPlayerController* PlayerContoller)->bool
			{
				return PlayerContoller->GetPlayerState<APlayerState>()->GetUniqueId() == netId;
			}))
		{
			Team2.RemoveSingle(*playerControllerPtr);
		}

		Team1.Add(PlayerController);
	}
	else
	{
		if (Team2.Num() > 4)
		{
			return;
		}

		if (Team2.FindByPredicate(
			[=](ACPP_TeamPlayerController* PlayerContoller)->bool
			{
				return PlayerContoller->GetPlayerState<APlayerState>()->GetUniqueId() == netId;
			}) != nullptr)
		{
			return;
		}

		if (ACPP_TeamPlayerController** playerControllerPtr = Team1.FindByPredicate(
			[=](ACPP_TeamPlayerController* PlayerContoller)->bool
			{
				return PlayerContoller->GetPlayerState<APlayerState>()->GetUniqueId() == netId;
			}))
		{
			Team1.RemoveSingle(*playerControllerPtr);
		}

		Team2.Add(PlayerController);
	}
	PlayerTeamChangedDelegate.Broadcast();
}

void ACPP_TeamGameState::MulticastCallPlayerChangedTeamDelegate_Implementation()
{
	PlayerTeamChangedDelegate.Broadcast();
}
