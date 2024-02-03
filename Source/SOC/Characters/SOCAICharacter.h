// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOCCharacter.h"
#include "SOCAI/Interfaces/SOCAIBehaviorInterface.h"
#include "SOCAICharacter.generated.h"

class USOCAIBehaviorComponent;
//AI Controlled character
UCLASS(Blueprintable)
class SOC_API ASOCAICharacter : public ASOCCharacter, public ISOCAIBehaviorInterface
{
	GENERATED_BODY()

#pragma region Framework
public:
	// Sets default values for this character's properties
	ASOCAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetOwner( AActor* NewOwner ) override;

	virtual void SpawnDefaultController() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion

#pragma region Behavior

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const override;

	virtual const AActor* GetAvatarActor() const override {return this;};

#pragma endregion




};
