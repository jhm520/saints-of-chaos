// © 2024 Jade Miller. All rights reserved

<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
#include "JadeActorSpawner.h"
========
#include "CoreActorSpawner.h"
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp

#include "CoreUtility/CoreUtilityBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/SpawnedActorInterface.h"
#include "Engine/World.h"
#pragma region Framework

// Sets default values
<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
AJadeActorSpawner::AJadeActorSpawner()
========
ACoreActorSpawner::ACoreActorSpawner()
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
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
<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
void AJadeActorSpawner::BeginPlay()
========
void ACoreActorSpawner::BeginPlay()
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
{
	Super::BeginPlay();
	
}

// Called every frame
<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
void AJadeActorSpawner::Tick(float DeltaTime)
========
void ACoreActorSpawner::Tick(float DeltaTime)
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
{
	Super::Tick(DeltaTime);

}

<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
void AJadeActorSpawner::Reset()
========
void ACoreActorSpawner::Reset()
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
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

<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
void AJadeActorSpawner::OnSpawnedActorDestroyed(AActor* DestroyedActor)
========
void ACoreActorSpawner::OnSpawnedActorDestroyed(AActor* DestroyedActor)
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
{
	SpawnedActors.Remove(DestroyedActor);
}

<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
AActor* AJadeActorSpawner::SpawnActor()
========
AActor* ACoreActorSpawner::SpawnActor()
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
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

<<<<<<<< HEAD:Source/CoreUtility/ActorSpawner/JadeActorSpawner.cpp
bool AJadeActorSpawner::CanTakeOwnership(AActor* InOwner) const
========
bool ACoreActorSpawner::CanTakeOwnership(AActor* InOwner) const
>>>>>>>> main:Source/CoreUtility/ActorSpawner/CoreActorSpawner.cpp
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
