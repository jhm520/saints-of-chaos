// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCRTSPlayerPawn.h"
#include "SelectionSystem/Components/SelectorComponent.h"

#pragma region Framework

// Sets default values for this pawn's properties
ASOCRTSPlayerPawn::ASOCRTSPlayerPawn()
{
	SelectorComponent = CreateDefaultSubobject<USelectorComponent>(TEXT("SelectorComponent"));
}

// Called when the game starts or when spawned
void ASOCRTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASOCRTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma endregion