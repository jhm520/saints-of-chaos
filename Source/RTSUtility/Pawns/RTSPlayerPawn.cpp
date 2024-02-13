// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "CoreUtility/EnhancedInput/EnhancedInputActionBindingCollection.h"
#include "GameFramework/SpringArmComponent.h"

#pragma region Framework

// Sets default values
ARTSPlayerPawn::ARTSPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	SceneRootComponent->SetupAttachment(GetRootComponent());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SceneRootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
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
	}
}
#pragma endregion

#pragma region Movement

void ARTSPlayerPawn::InputAction_Movement(const FInputActionInstance& Instance, EInputActionBinding AbilityInput, const UInputAction* InputAction)
{
	if (!InputAction)
	{
		return;
	}
	
	const FVector Axis = Instance.GetValue().Get<FVector>();

	const FVector& ForwardVector = GetActorForwardVector();
	const FVector& RightVector = GetActorRightVector();

	const float ForwardValue = FVector::DotProduct(Axis, ForwardVector);
	const float RightValue = FVector::DotProduct(Axis, RightVector);

	AddMovementInput(ForwardVector, ForwardValue);
	AddMovementInput(RightVector, RightValue);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Axis: %s"), *Axis.ToString()));
}
#pragma endregion
