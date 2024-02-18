// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_BaseCharacterComponent.h"
#include "CPP_BaseHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUPERMEGASHOOTER_API UCPP_BaseHealthComponent : public UCPP_BaseCharacterComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	virtual bool ApplyDamage(AActor* Instigator, AActor* DamageCauser) { return true; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health Component")
	virtual inline int32 GetHealth() const;

protected:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Health Component")
	int32 Health = 100;

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "Health Component")
	bool bAlive = true;
};
