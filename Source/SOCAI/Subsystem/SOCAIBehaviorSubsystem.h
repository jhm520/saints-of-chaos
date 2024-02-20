// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SOCAIBehaviorSubsystem.generated.h"

class ASOCAIBehaviorManager;
/**
 * 
 */
UCLASS()
class SOCAI_API USOCAIBehaviorSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

#pragma region Framework
public:
	USOCAIBehaviorSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Behavior")
	static USOCAIBehaviorSubsystem* Get(const UObject* WorldContext);
#pragma endregion

#pragma region Behavior Subsystem
protected:
	UPROPERTY()
	TArray<ASOCAIBehaviorManager*> RegisteredBehaviorManagers;
public:
	
	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void Register(ASOCAIBehaviorManager* Actor);

	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void Unregister(ASOCAIBehaviorManager* Actor);
	
	UFUNCTION(BlueprintPure, Category = "Behavior")
	TArray<ASOCAIBehaviorManager*> GetAllBehaviorManagers();

	UFUNCTION(BlueprintPure, Category = "Behavior")
	USOCAIBehavior* GetBehavior(const FGameplayTag& InBehaviorTag);
	
#pragma endregion
	
};
