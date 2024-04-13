// © 2024 John Henry Miller. All rights reserved

#include "ClickingComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTypes.h"

#pragma region Framework

// Sets default values for this component's properties
UClickingComponent::UClickingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UClickingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UClickingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Clicking

void UClickingComponent::OnActorClicked(AActor* ClickedActor, UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwner());

	if (!AbilitySystemInterface)
	{
		return;
	}

	UAbilitySystemComponent* ClickPCASC = AbilitySystemInterface->GetAbilitySystemComponent();

	if (!ClickPCASC)
	{
		return;
	}

	for (const FClickInteraction& ClickInteraction : ClickInteractions)
	{
		DoClickInteraction(ClickInteraction, ClickedActor, TouchedComponent, ButtonPressed);
	}
}

void UClickingComponent::DoClickInteraction(const FClickInteraction& ClickInteraction, AActor* ClickedActor, UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	TArray<FGameplayTag> ClickGameplayEventTags;
	
	ClickInteraction.ClickGameplayEventTags.GetGameplayTagArray(ClickGameplayEventTags);

	for (const FGameplayTag& GameplayEventTag : ClickGameplayEventTags)
	{
		FGameplayEventData Payload = FGameplayEventData();

		Payload.Instigator = GetOwner();
		Payload.Target = ClickedActor;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), GameplayEventTag, Payload);
	}
}


#pragma endregion