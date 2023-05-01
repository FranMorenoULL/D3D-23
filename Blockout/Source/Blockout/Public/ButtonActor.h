// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonActor.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOCKOUT_API AButtonActor : public AActor
{
	GENERATED_BODY()

public:
	FOnButtonDown OnButtonDown;
	FOnButtonUp OnButtonUp;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ButtonMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SwitchMesh;

private:
	UPROPERTY()
	TArray<AActor*> OverlappingActors;

public:
	AButtonActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorEntersCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnActorExitsCollision (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonDownBP();
	UFUNCTION(BlueprintImplementableEvent)
	void OnButtonUpBP();
		
};
