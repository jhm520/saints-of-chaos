// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SOCAI/SOCAIGameplayTags.h"
#include "SOCAIBehaviorComponent.generated.h"

//component for actors that are controlled by the SOCAI system and AI Behaviors
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOCAI_API USOCAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this component's properties
	USOCAIBehaviorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Behavior
protected:

	UPROPERTY(Transient)
	FGameplayTag CurrentBehaviorState = SOCAIBehaviorTags::Behavior;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<ASOCAIBehaviorManager> BehaviorManager = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> CurrentBehavior = nullptr;

	virtual void TickUpdateBehavior(const float DeltaSeconds);

	UFUNCTION(BlueprintNativeEvent, Category = "AI|Behavior")
	void DoAction(const FSOCAIAction& InAction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag RootBehaviorState = SOCAIBehaviorTags::Behavior;
	
public:
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	ASOCAIBehaviorManager* GetBehaviorManager(){return BehaviorManager;};
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	bool SetBehaviorState(const FGameplayTag& InBehaviorTag);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetCurrentBehaviorState() {return CurrentBehaviorState;};

	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	USOCAIBehavior* GetBehavior(const FGameplayTag& InBehaviorTag);

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const USOCAIBehavior* GetCurrentBehavior(){return CurrentBehavior;};

	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	const FGameplayTag& GetRootBehaviorState(){return RootBehaviorState;};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	TSubclassOf<ASOCAIBehaviorManager> BehaviorManagerClass;

	UFUNCTION()
	bool TryCreateBehaviorManager();
#pragma endregion

};
