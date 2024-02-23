// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/CPP_MainUIWidget.h"
#include "Components/Image.h"
#include "UI/Weapons/CPP_WeaponPanelWidget.h"
#include "UI/Player/CPP_HealthStatsWidget.h"
#include "UI/Common/KillFeed/CPP_KillFeedWidget.h"
#include "UI/Common/Time/CPP_TimeWidget.h"

UCPP_KillFeedWidget* UCPP_MainUIWidget::GetKillFeedWidget() const
{
	return KillFeedWidget;
}
