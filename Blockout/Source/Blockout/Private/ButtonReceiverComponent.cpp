// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonReceiverComponent.h"

#include "ButtonActor.h"

UButtonReceiverComponent::UButtonReceiverComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UButtonReceiverComponent::BeginPlay()
{
	Super::BeginPlay();

	for (AButtonActor* RequiredButton : RequiredButtons)
	{
		if (RequiredButton)
		{
			RequiredButton->OnButtonDown.AddUniqueDynamic(this, &UButtonReceiverComponent::OnRequiredButtonDown);
			RequiredButton->OnButtonUp.AddUniqueDynamic(this, &UButtonReceiverComponent::OnRequiredButtonUp);
		}
	}
}

void UButtonReceiverComponent::OnRequiredButtonDown()
{
	++RequiredButtonDownCounter;
	
	if (RequiredButtonDownCounter == RequiredButtons.Num())
	{
		for (AButtonActor* RequiredButton : RequiredButtons)
		{
			if (RequiredButton)
			{
				RequiredButton->OnButtonDown.RemoveDynamic(this, &UButtonReceiverComponent::OnRequiredButtonDown);
				RequiredButton->OnButtonUp.RemoveDynamic(this, &UButtonReceiverComponent::OnRequiredButtonUp);
			}
		}
		OnButtonReceiverTriggered.Broadcast();
	}
}

void UButtonReceiverComponent::OnRequiredButtonUp()
{
	--RequiredButtonDownCounter;
}
