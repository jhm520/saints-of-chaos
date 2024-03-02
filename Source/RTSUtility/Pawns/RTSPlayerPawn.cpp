// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "CoreUtility/EnhancedInput/EnhancedInputActionBindingCollection.h"
#include "CoreUtility/SpringArm/Components/SpringArmComponentBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "RTSUtility/Components/RTSPlayerMouseComponent.h"

#pragma region Framework

// Sets default values
ARTSPlayerPawn::ARTSPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SetRootComponent(SceneRootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponentBase>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SceneRootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	CameraZoomDistanceIncrement = 250.0f;
	MinimumCameraZoomDistance = 300.0f;
	MaximumCameraZoomDistance = 1500000.0f;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	RTSPlayerMouseComponent = CreateDefaultSubobject<URTSPlayerMouseComponent>(TEXT("RTSPlayerMouseComponent"));
	
}

// Called when the game starts or when spawned
void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	RTSPlayerMouseComponent->OnMouseScreenEdgeScroll.AddDynamic(this, &ARTSPlayerPawn::OnPlayerMouseScreenEdgeScroll);
	
}

// Called every frame
void ARTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Axis: %s"), *ControlInputVector.ToString()));
	
}

#pragma endregion

#pragma region Input

void ARTSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputActionBindingCollection)
	{
		UE_LOG(LogTemp, Error, TEXT("InputActionBindingCollection is not set in %s"), *GetName());
		return;
	}

	APlayerController* PC = GetController<APlayerController>();

	if (!PC)
	{
		return;
	}
	
	if(InputActionBindingCollection->InputContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputActionBindingCollection->InputContext, 0);
		}
	}
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	for (const FEnhancedInputActionBinding& Binding : InputActionBindingCollection->InputActionBindings)
	{
		if (!Binding.InputAction)
		{
			continue;
		}
	
		// You can bind to any of the trigger events here by changing the "ETriggerEvent" enum value
		Input->BindAction(Binding.InputAction, ETriggerEvent::Triggered, this, &ARTSPlayerPawn::InputAction, Binding.InputActionBinding, Binding.InputAction.Get());
		// You can bind to any of the trigger events here by changing the "ETriggerEvent" enum value
		Input->BindAction(Binding.InputAction, ETriggerEvent::Completed, this, &ARTSPlayerPawn::InputAction, Binding.InputActionBinding, Binding.InputAction.Get());
	}
}

void ARTSPlayerPawn::InputAction(const FInputActionInstance& Instance, EInputActionBinding AbilityInput, const UInputAction* InputAction)
{
	// Get the value of the Input Action for whatever type you want here...
	FVector VectorValue = Instance.GetValue().Get<FVector>();
	FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
	float FloatValue = Instance.GetValue().Get<float>(); 
	bool BoolValue = Instance.GetValue().Get<bool>();

	// Do your cool stuff here!

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("InputAction: %s"), *InputAction->GetName()));
	switch (AbilityInput)
	{
		case EInputActionBinding::None:
		{
			break;
		}
		case EInputActionBinding::Movement:
		{
			InputAction_Movement(Instance, AbilityInput, InputAction);
			break;
		}
		case EInputActionBinding::CameraZoom:
		{
			InputAction_CameraZoom(Instance, AbilityInput, InputAction);
			break;
		}
		default:
		{
			InputAction_Ability(Instance, AbilityInput, InputAction);
			break;
		}
	}
}
#pragma endregion

#pragma region Camera

void ARTSPlayerPawn::InputAction_CameraZoom(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction)
{
	const float Value = Instance.GetValue().Get<float>();
	
	DoCameraZoom(Value);
}

void ARTSPlayerPawn::DoCameraZoom(float ZoomValue)
{
	float NewTargetArmLength = SpringArmComponent->GetDesiredSpringArmLength();

	NewTargetArmLength += ZoomValue > 0.0f ? -CameraZoomDistanceIncrement : CameraZoomDistanceIncrement;
	
	SpringArmComponent->SetDesiredSpringArmLength(FMath::Clamp(NewTargetArmLength, MinimumCameraZoomDistance, MaximumCameraZoomDistance));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("NewTargetArmLength: %f"), NewTargetArmLength));
}


void ARTSPlayerPawn::InputAction_Ability(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction)
{
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(this);
	
	if (!AbilitySystemInterface)
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!InputAction)
	{
		return;
	}
	
	const bool bIsPressed = Instance.GetValue().Get<bool>();
	
	if (bIsPressed)
	{
		AbilitySystemComponent->PressInputID(GetTypeHash(InputAction));
	}
	else
	{
		AbilitySystemComponent->ReleaseInputID(GetTypeHash(InputAction));
	}
}

void ARTSPlayerPawn::DoContextCommand()
{
	
}


#pragma endregion

#pragma region Movement

void ARTSPlayerPawn::InputAction_Movement(const FInputActionInstance& Instance, EInputActionBinding ActionInput, const UInputAction* InputAction)
{
	if (!InputAction)
	{
		return;
	}
	
	const FVector& Axis = Instance.GetValue().Get<FVector>();

	DoMovement(Axis);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Axis: %s"), *Axis.ToString()));
}

void ARTSPlayerPawn::DoMovement(const FVector& Axis)
{
	const FVector& ForwardVector = GetActorForwardVector();
	const FVector& RightVector = GetActorRightVector();

	const float ForwardValue = Axis.X;
	const float RightValue = Axis.Y;

	AddMovementInput(ForwardVector, ForwardValue);
	AddMovementInput(RightVector, RightValue);
}

#pragma endregion

#pragma region Mouse

void ARTSPlayerPawn::OnPlayerMouseScreenEdgeScroll(const FVector2D& Direction)
{
	const FVector& ThreeDirection = FVector(Direction.X, Direction.Y, 0.0f);
	
	DoMovement(ThreeDirection);
}

#pragma endregion

#pragma region Attitude System

EAttitude ARTSPlayerPawn::GetAttitudeTowards_Implementation(AActor* Other) const
{
	return EAttitude::Neutral;
}

#pragma endregion
