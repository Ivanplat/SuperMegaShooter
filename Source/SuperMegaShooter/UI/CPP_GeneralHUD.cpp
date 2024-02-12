// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPP_GeneralHUD.h"
#include "UI/Common/CPP_MainUIWidget.h"


inline UCPP_MainUIWidget* ACPP_GeneralHUD::GetMainUIWidget() const
{
	return MainUIWidget;
}

void ACPP_GeneralHUD::CreateMainUIWidget()
{
	if (!MainUIWidget && MainUIWidgetClass != nullptr && GetOwningPlayerController())
	{
		MainUIWidget = CreateWidget<UCPP_MainUIWidget>(GetOwningPlayerController(), MainUIWidgetClass);
		MainUIWidget->AddToViewport();
	}
}

void ACPP_GeneralHUD::DestroyMainUIWidget()
{
	if (MainUIWidget)
	{
		MainUIWidget->RemoveFromParent();
		MainUIWidget = nullptr;
	}
}

void ACPP_GeneralHUD::OnPlayerCharacterReady()
{
	CreateMainUIWidget();
}

void ACPP_GeneralHUD::OnPlayerCharacterDead()
{
	DestroyMainUIWidget();
}
