// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/KillFeed/CPP_KillFeedMessageWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

inline UCPP_KillFeedMessageWidget* UCPP_KillFeedMessageWidget::SetKillerNickname(FText NewName)
{
	KillerNickname->SetText(NewName);
	return this;
}

inline UCPP_KillFeedMessageWidget* UCPP_KillFeedMessageWidget::SetVictimNickname(FText NewName)
{
	VictimNickname->SetText(NewName);
	return this;
}

inline UCPP_KillFeedMessageWidget* UCPP_KillFeedMessageWidget::SetWeponImageTexture(UTexture2D* NewImageTexture)
{
	FSlateBrush br;

	br.SetResourceObject(NewImageTexture);
	br.TintColor = FColor::White;
	I_WeaponImage->SetBrush(br);

	return this;
}
