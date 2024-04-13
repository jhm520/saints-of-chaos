// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CoreUtility/AutoOwnership/Interfaces/AutoOwnershipInterface.h"
#include "GameFramework/Actor.h"
#include "ActorSpawner.generated.h"

class UCapsuleComponent;

//this is an actor that can be placed in levels and will spawn other actors
UCLASS()
class COREUTILITY_API AActorSpawner : public AActor, public IAutoOwnershipInterface
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Reset() override;

#pragma endregion

#pragma region Capsule

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
#pragma endregion
	
#pragma region ActorSpawner

protected:
	//the maximum number of actors that can be spawned by this actor at any given time
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Spawner")
	int32 MaxSpawnedActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Actor Spawner")
	TSubclassOf<AActor> DefaultActorClassToSpawn;

	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> SpawnedActors;

	UFUNCTION()
	void OnSpawnedActorDestroyed(AActor* DestroyedActor);

public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Actor Spawner")
	AActor* SpawnActor();

#pragma endregion

#pragma region Auto Ownership
public:

	virtual bool CanTakeOwnership(AActor* InOwner) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Ownership")
	int32 OwningControllerId;
	
#pragma endregion

};
