// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ClickingComponent.generated.h"

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct COREUTILITY_API FClickInteraction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clicking")
	FGameplayTagContainer ClickGameplayEventTags = FGameplayTagContainer();
	
	FClickInteraction(){}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREUTILITY_API UClickingComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework

public:	
	// Sets default values for this component's properties
	UClickingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
#pragma endregion

#pragma region Clicking

	UFUNCTION()
	void OnActorClicked(AActor* ClickedActor, UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	//an array that holds all the possible click interactions for this actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Clicking")
	TArray<FClickInteraction> ClickInteractions;

	void DoClickInteraction(const FClickInteraction& ClickInteraction, AActor* ClickedActor, UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

#pragma endregion
		
};
