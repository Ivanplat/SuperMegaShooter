// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/Game/CPP_BaseGameState.h"
#include "CPP_TeamGameState.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API ACPP_TeamGameState : public ACPP_BaseGameState
{
	GENERATED_BODY()
	
private:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerTeamChanged);
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerChangeTeam(class ACPP_TeamPlayerController* PlayerController, int32 TeamIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Team Game State | Teams")
	inline void GetTeam1(TArray<class ACPP_TeamPlayerController*>& OutValue) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Team Game State | Teams")
	inline void GetTeam2(TArray<class ACPP_TeamPlayerController*>& OutValue) const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	virtual void ServerChangeTeam_Implementation(class ACPP_TeamPlayerController* PlayerController, int32 TeamIndex);

	UFUNCTION()
	virtual void MulticastCallPlayerChangedTeamDelegate_Implementation();

public:
	UPROPERTY(BlueprintAssignable, Category = "Team Game State | Teams")
	FPlayerTeamChanged PlayerTeamChangedDelegate;

protected:
	UPROPERTY(Replicated, ReplicatedUsing = MulticastCallPlayerChangedTeamDelegate_Implementation)
	TArray<class ACPP_TeamPlayerController*> Team1;

	UPROPERTY(Replicated, ReplicatedUsing = MulticastCallPlayerChangedTeamDelegate_Implementation)
	TArray<class ACPP_TeamPlayerController*> Team2;
};
