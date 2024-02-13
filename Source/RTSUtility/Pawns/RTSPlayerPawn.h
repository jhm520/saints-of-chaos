// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTSPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UEnhancedInputActionBindingCollection;

UCLASS()
class RTSUTILITY_API ARTSPlayerPawn : public ACharacter
{
	GENERATED_BODY()

#pragma region Framework
public:
	// Sets default values for this pawn's properties
	ARTSPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma endregion

#pragma region Root

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USceneComponent> SceneRootComponent;

#pragma endregion

#pragma region Camera
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

#pragma endregion
	
#pragma region Input
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION()
	void InputAction(const FInputActionInstance& Instance, EInputActionBinding AbilityInput, const UInputAction* InputAction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UEnhancedInputActionBindingCollection> InputActionBindingCollection;

#pragma endregion

#pragma region Movement

	UFUNCTION()
	void InputAction_Movement(const FInputActionInstance& Instance, EInputActionBinding AbilityInput, const UInputAction* InputAction);
#pragma endregion

};
