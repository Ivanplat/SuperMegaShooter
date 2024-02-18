// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CPP_DeathMatchGameMode.h"

void ACPP_DeathMatchGameMode::BeginPlay()
{
	ACPP_BaseGameMode::BeginPlay();

	FTimerHandle th;
	FTimerDelegate td;

	td.BindLambda
	(
		[&]()
		{
			MulticastCallGameStartedDelegate();
		}
	);

	GetWorld()->GetTimerManager().SetTimer(th, td, 1.0f, false, 1.0f);
}
