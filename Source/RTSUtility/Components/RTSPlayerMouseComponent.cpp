// © 2024 John Henry Miller. All rights reserved

#include "RTSPlayerMouseComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

#pragma region Framework

// Sets default values for this component's properties
URTSPlayerMouseComponent::URTSPlayerMouseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(false);

	bRTSMouseEnabled = true;
	bRTSMouseEnabledByDefault = true;

	MouseScrollBorder = 10.0f;
	// ...
}

// Called when the game starts
void URTSPlayerMouseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SetRTSMouseEnabled(bRTSMouseEnabledByDefault);
}


// Called every frame
void URTSPlayerMouseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsRTSMouseEnabled())
	{
		CheckMouseScrolling();
	}

	// ...
}
#pragma endregion

#pragma region Mouse
void URTSPlayerMouseComponent::SetRTSMouseEnabled(bool bEnabled)
{
	APlayerController* MouseController = GetMouseController();

	if (!MouseController)
	{
		return;
	}
	
	bRTSMouseEnabled = bEnabled;

	MouseController->SetShowMouseCursor(bEnabled);

	if (bEnabled)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(MouseController, nullptr, EMouseLockMode::LockAlways, false);
	}
	else
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(MouseController);
	}

	
}
#pragma endregion

#pragma region Controller

//get the player controller responsible for moving this mouse
APlayerController* URTSPlayerMouseComponent::GetMouseController() const
{
	AActor* MouseControllerOwner = GetOwner();

	//follow the chain of ownership up until we reach nullptr or a player controller
	while (MouseControllerOwner)
	{
		APlayerController* PlayerController = Cast<APlayerController>(MouseControllerOwner);
		if (PlayerController)
		{
			return PlayerController;
		}

		MouseControllerOwner = MouseControllerOwner->GetOwner();
	}

	return nullptr;
}

#pragma endregion

#pragma region Scrolling

void URTSPlayerMouseComponent::CheckMouseScrolling()
{
	APlayerController* MouseController = GetMouseController();

	if (!MouseController)
	{
		return;
	}

	int32 SizeX;
	int32 SizeY;
	
	MouseController->GetViewportSize(SizeX,SizeY);

	float MousePositionX;
	float MousePositionY;
	
	const bool bGotMouse = MouseController->GetMousePosition(MousePositionX, MousePositionY);

	if (!bGotMouse)
	{
		return;
	}

	const bool bScrollingUp = MousePositionY <= MouseScrollBorder;
	const bool bScrollingDown = MousePositionY >= SizeY - MouseScrollBorder;
	const bool bScrollingLeft = MousePositionX <= MouseScrollBorder;
	const bool bScrollingRight = MousePositionX >= SizeX - MouseScrollBorder;

	if (!bScrollingUp && !bScrollingDown && !bScrollingLeft && !bScrollingRight)
	{
		return;
	}
	
	FVector2D ScrollDirection = FVector2D::ZeroVector;

	ScrollDirection.X = bScrollingUp ? 1.0f : bScrollingDown ? -1.0f : 0.0f;
	ScrollDirection.Y = bScrollingRight ? 1.0f : bScrollingLeft ? -1.0f : 0.0f;

	OnMouseScreenEdgeScroll.Broadcast(ScrollDirection);
}

#pragma endregion