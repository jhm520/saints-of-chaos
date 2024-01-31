// Fill out your copyright notice in the Description page of Project Settings.


#include "AggroSystemComponent.h"

#include "AggroSystem/Interfaces/AggroInterface.h"
#include "Kismet/KismetSystemLibrary.h"

#pragma region Framework

// Sets default values for this component's properties
UAggroSystemComponent::UAggroSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UAggroSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UAggroSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

#pragma endregion

#pragma region Framework

AActor* UAggroSystemComponent::FindClosestTarget()
{
	TArray<AActor*> AggroTargets;

	FindTargets(AggroTargets);

	AActor* ClosestTarget = nullptr;

	float ClosestTargetDistance = UE_MAX_FLT;

	for (AActor* Target : AggroTargets)
	{
		if (!Target)
		{
			continue;
		}

		if (!ClosestTarget)
		{
			ClosestTarget = Target;
			ClosestTargetDistance = FVector::Dist(Target->GetActorLocation(), GetOwner()->GetActorLocation());
			continue;
		}

		const float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), GetOwner()->GetActorLocation());

		if (DistanceToTarget < ClosestTargetDistance)
		{
			ClosestTarget = Target;
			ClosestTargetDistance = DistanceToTarget;
		}
	}

	return ClosestTarget;
}

bool UAggroSystemComponent::ShouldAggro(AActor* AggroTarget)
{
	if (!AggroTarget)
	{
		return false;
	}

	IAggroInterface* AggroInterface = Cast<IAggroInterface>(GetOwner());

	if (!AggroInterface)
	{
		return false;
	}

	return AggroInterface->ShouldAggro(AggroTarget);
}

void UAggroSystemComponent::FindTargets(TArray<AActor*>& OutTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	
	const bool bOverlapResult = UKismetSystemLibrary::SphereOverlapActors(this, GetOwner()->GetActorLocation(), AggroRadius, AggroObjectTypes, TSubclassOf<APawn>(), ActorsToIgnore, OutTargets);

	for (AActor* Target : OutTargets)
	{
		if (!Target)
		{
			continue;
		}

		if (!ShouldAggro(Target))
		{
			OutTargets.Remove(Target);
		}
	}
}


#pragma endregion