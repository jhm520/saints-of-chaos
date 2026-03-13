// © 2024 Jade Miller. All rights reserved

#include "CoreActorSpawner.h"

#include "CoreUtility/CoreUtilityBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/SpawnedActorInterface.h"
#include "Engine/World.h"
#pragma region Framework

// Sets default values
ACoreActorSpawner::ACoreActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	OwningControllerId = -1;

	MaxSpawnedActors = 1;
}

// Called when the game starts or when spawned
void ACoreActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoreActorSpawner::Reset()
{
	Super::Reset();

	TArray<AActor*> LocalActors = SpawnedActors;

	for (AActor* Actor : LocalActors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		Actor->Destroy();
	}
}

#pragma endregion

#pragma region ActorSpawner

void ACoreActorSpawner::OnSpawnedActorDestroyed(AActor* DestroyedActor)
{
	SpawnedActors.Remove(DestroyedActor);
}

AActor* ACoreActorSpawner::SpawnActor()
{
	if (!HasAuthority())
	{
		return nullptr;
	}

	if (!GetOwner()->GetWorld())
	{
		return nullptr;
	}
	
	if (SpawnedActors.Num() >= MaxSpawnedActors)
	{
		return nullptr;
	}
		
	AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(DefaultActorClassToSpawn, GetActorTransform(), GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (!NewActor)
	{
		return nullptr;
	}

	const bool bImplementsInterface = NewActor->Implements<USpawnedActorInterface>();

	if (bImplementsInterface)
	{
		ISpawnedActorInterface::Execute_PreActorSpawnFinished(NewActor, this);
	}
	
	NewActor->FinishSpawning(NewActor->GetActorTransform());
	
	if (bImplementsInterface)
	{
		ISpawnedActorInterface::Execute_PostActorSpawnFinished(NewActor, this);
	}

	SpawnedActors.AddUnique(NewActor);
	
	NewActor->OnDestroyed.AddDynamic(this, &ACoreActorSpawner::OnSpawnedActorDestroyed);

	return NewActor;
}

#pragma endregion

#pragma region Auto Ownership

bool ACoreActorSpawner::CanTakeOwnership(AActor* InOwner) const
{
	if (!InOwner || !InOwner->HasAuthority())
	{
		return false;
	}
	
	if (OwningControllerId == -1)
	{
		return false;
	}

	AController* Controller = Cast<AController>(InOwner);
	
	if (!Controller)
	{
		return false;
	}

	const int32 ControllerId = UCoreUtilityBlueprintLibrary::GetAuthPlayerControllerId(this, Controller);
	
	if (ControllerId != OwningControllerId)
	{
		return false;
	}
	
	return true;
}

#pragma endregion
