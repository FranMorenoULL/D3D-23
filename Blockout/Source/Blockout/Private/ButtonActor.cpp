// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonActor.h"

#include "ButtonActivaterInterface.h"
#include "Components/BoxComponent.h"

AButtonActor::AButtonActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	SetRootComponent(BoxCollision);
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Button Mesh");
	ButtonMesh->SetupAttachment(BoxCollision);
	
	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>("Switch Mesh");
	SwitchMesh->SetupAttachment(ButtonMesh);
}

void AButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AButtonActor::OnActorEntersCollision);
	BoxCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &AButtonActor::OnActorExitsCollision);
	
	OnButtonDown.AddUniqueDynamic(this, &AButtonActor::OnButtonDownBP);
	OnButtonUp.AddUniqueDynamic(this, &AButtonActor::OnButtonUpBP);
}

void AButtonActor::OnActorEntersCollision(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!OtherActor || !OtherActor->Implements<UButtonActivaterInterface>())
	{
		return;
	}
	if (OverlappingActors.IsEmpty())
	{
		OnButtonDown.Broadcast();
	}
	OverlappingActors.AddUnique(OtherActor);
}

void AButtonActor::OnActorExitsCollision(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, int32)
{
	if (!OtherActor || !OtherActor->Implements<UButtonActivaterInterface>())
	{
		return;
	}
	OverlappingActors.RemoveSingle(OtherActor);
	if (OverlappingActors.IsEmpty())
	{
		OnButtonUp.Broadcast();
	}
}
