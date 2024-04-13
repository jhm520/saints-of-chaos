// © 2024 John Henry Miller. All rights reserved

#include "ClickableActorComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "CoreUtility/Clicking/Interfaces/ClickableActorInterface.h"
#include "CoreUtility/Clicking/Interfaces/ClickingInterface.h"
#include "Kismet/GameplayStatics.h"
#include "ClickingComponent.h"

#pragma region Framework

// Sets default values for this component's properties
UClickableActorComponent::UClickableActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bIsClickable = true;
	// ...
}


// Called when the game starts
void UClickableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	SetupClickable();
}


// Called every frame
void UClickableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Clickable

void UClickableActorComponent::SetupClickable()
{
	IClickableActorInterface* ClickableActorInterface = Cast<IClickableActorInterface>(GetOwner());

	if (!ClickableActorInterface)
	{
		return;
	}
	
	UPrimitiveComponent* ClickableComponent = ClickableActorInterface->GetClickableComponent();

	if (!ClickableComponent)
	{
		return;
	}

	ClickableComponent->OnClicked.AddDynamic(this, &UClickableActorComponent::OnActorClicked);
}

void UClickableActorComponent::OnActorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (!bIsClickable)
	{
		return;
	}
	
	//get the player controller that clicked on this character, the local player
	APlayerController* ClickPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!ClickPC)
	{
		return;
	}

	IClickingInterface* ClickingInterface = Cast<IClickingInterface>(ClickPC);

	if (!ClickingInterface)
	{
		return;
	}

	UClickingComponent* ClickingComponent = ClickingInterface->GetClickingComponent();

	if (!ClickingComponent)
	{
		return;
	}

	ClickingComponent->OnActorClicked(GetOwner(), TouchedComponent, ButtonPressed);
	
}

#pragma endregion
