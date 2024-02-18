// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_BaseCharacterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERMEGASHOOTER_API UCPP_BaseCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPP_BaseCharacterComponent();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Component")
	virtual inline class ACPP_BaseCharacter* GetComponentOwner() const;

	template<class T>
	inline T* GetComponentOwner() const
	{
		return Cast<T>(GetComponentOwner());
	}

protected:
	virtual void BeginPlay() override;

protected:	
	UPROPERTY()
	class ACPP_BaseCharacter* ComponentOwner = nullptr;
		
};
