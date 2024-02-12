// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UI/CPP_BaseWidget.h"
#include "CPP_WeaponPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMEGASHOOTER_API UCPP_WeaponPanelWidget : public UCPP_BaseWidget
{
	GENERATED_BODY()

public:
	virtual void SynchronizeProperties() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UCPP_WeaponSlotWidget* MainWeaponSlotWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UCPP_WeaponSlotWidget* SecondaryWeaponSlotWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UCPP_WeaponSlotWidget* MeleeWeaponSlotWidget;
};
