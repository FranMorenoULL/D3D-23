// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonReceiverComponent.generated.h"

class AButtonActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReceiverTriggered);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOCKOUT_API UButtonReceiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonReceiverTriggered OnButtonReceiverTriggered;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AButtonActor*> RequiredButtons;

private:
	int32 RequiredButtonDownCounter = 0;
	
public:
	UButtonReceiverComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRequiredButtonDown();
	UFUNCTION()
	void OnRequiredButtonUp();
};
