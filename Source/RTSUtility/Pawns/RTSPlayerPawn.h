// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/Attitude/AttitudeInterface.h"
#include "GameFramework/Pawn.h"
#include "RTSPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponentBase;
class UEnhancedInputActionBindingCollection;
class UFloatingPawnMovement;
class URTSPlayerMouseComponent;

UCLASS()
class RTSUTILITY_API ARTSPlayerPawn : public APawn, public IAttitudeInterface
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
protected:
	
	UFUNCTION()
	void InputAction_CameraZoom(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction);

	void DoCameraZoom(float ZoomValue);

	UFUNCTION()
	void InputAction_Ability(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction);
	
	void DoContextCommand();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraZoomDistanceIncrement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float MinimumCameraZoomDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float MaximumCameraZoomDistance;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponentBase> SpringArmComponent;

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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	
	UFUNCTION()
	void InputAction_Movement(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction);

	UFUNCTION()
	void DoMovement(const FVector& Axis);
#pragma endregion

#pragma region Mouse

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mouse")
	TObjectPtr<URTSPlayerMouseComponent> RTSPlayerMouseComponent;

	UFUNCTION()
	void OnPlayerMouseScreenEdgeScroll(const FVector2D& Direction);

#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion
};
