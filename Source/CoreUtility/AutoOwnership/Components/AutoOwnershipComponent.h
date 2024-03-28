// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AutoOwnershipComponent.generated.h"

// Auto Ownership Component is a component that makes its owner automatically take ownership of designated actors at begin play
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREUTILITY_API UAutoOwnershipComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Framework
public:	
	// Sets default values for this component's properties
	UAutoOwnershipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Auto Ownership

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Auto Ownership")
	TArray<AActor*> GetAutoOwnedActors(TSubclassOf<AActor> ActorClassFilter = nullptr) const;

protected:
	
	//Actors that this component has automatically taken ownership of
	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> AutoOwnedActors;
	
	// Automatically takes ownership of designated actors at begin play
	UFUNCTION()
	void AutoTakeOwnership();
	
	UFUNCTION()
	void OnAutoOwnedActorDestroyed(AActor* DestroyedActor);
#pragma endregion

};
