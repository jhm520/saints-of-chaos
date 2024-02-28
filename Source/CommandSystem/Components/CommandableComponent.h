// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CommandableComponent.generated.h"

//struct to represent an AIController's current action
USTRUCT(BlueprintType)
struct COMMANDSYSTEM_API FCommandInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FGameplayTag CommandTag = FGameplayTag::EmptyTag;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FVector TargetLocation = FVector::ZeroVector;

	FCommandInfo(){}
};

//this is a component that is meant to be added to actors that are selectable by selectors
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDSYSTEM_API UCommandableComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Framework

public:	
	// Sets default values for this component's properties
	UCommandableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

};
