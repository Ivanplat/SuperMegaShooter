// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/KillFeed/CPP_KillFeedWidget.h"
#include "Components/VerticalBox.h"
#include "UI/Common/KillFeed/CPP_KillFeedMessageWidget.h"

void UCPP_KillFeedWidget::AddKillFeedMessage(UCPP_KillFeedMessageWidget* WidgetToAdd)
{
	VB_KillFeed->AddChildToVerticalBox(WidgetToAdd);
	KillFeedQueue.Enqueue(WidgetToAdd);

	FTimerHandle th;
	FTimerDelegate td;

	td.BindUFunction(this, FName("RemoveFirstKillFeedMessage"));

	GetWorld()->GetTimerManager().SetTimer(th, td, RemovingFromKillFeedDelay, false, RemovingFromKillFeedDelay);
}

void UCPP_KillFeedWidget::RemoveFirstKillFeedMessage()
{
	if (!KillFeedQueue.IsEmpty())
	{
		UCPP_KillFeedMessageWidget* messageWidget = nullptr;

		KillFeedQueue.Peek(messageWidget);
		KillFeedQueue.Pop();

		messageWidget->DestroyKillFeedMessage();
	}
}
