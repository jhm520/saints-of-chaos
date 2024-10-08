// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SOCAI/SOCAIGameplayTags.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIBehaviorComponent.generated.h"

class ASOCAIBehaviorManager;

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Behavior
protected:

	UPROPERTY(Transient)
	FGameplayTag CurrentBehaviorState = SOCAIBehaviorTags::Behavior;

	UPROPERTY(ReplicatedUsing="OnRep_BehaviorManager", BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<ASOCAIBehaviorManager> BehaviorManager = nullptr;

	UFUNCTION()
	void OnRep_BehaviorManager();

	UPROPERTY(BlueprintReadOnly, Category = "AI|Behavior")
	TObjectPtr<USOCAIBehavior> CurrentBehavior = nullptr;

	virtual void TickUpdateBehavior(const float DeltaSeconds);

	virtual void DoAction(const FSOCAIAction& InAction);

	virtual void OnBehaviorChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction);

	virtual void OnActionChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI|Behavior")
	FGameplayTag RootBehaviorState = SOCAIBehaviorTags::Behavior;

	UPROPERTY(ReplicatedUsing="OnRep_CurrentAction", Transient, BlueprintReadOnly, Category = "AI|Behavior")
	FSOCAIAction CurrentAction;

	UFUNCTION()
	void OnRep_CurrentAction(const FSOCAIAction& PreviousAction);

	
public:

	void InitBehaviorSystem(AActor* InDirector);
	
	UFUNCTION(BlueprintPure, Category = "AI|Behavior")
	ASOCAIBehaviorManager* GetBehaviorManager(){return BehaviorManager;};
	
	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	bool SetBehaviorState(const FGameplayTag& InBehaviorTag);

	const FSOCAIAction& GetCurrentAction() const {return CurrentAction;};

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

#pragma region Director
public:
	//returns the actor that is directing the behavior of this actor
	AActor* GetDirector() const { return Director; }

	//sets the actor that directs the behavior of this actor
	void SetDirector(AActor* InDirector);

protected:
	UPROPERTY(ReplicatedUsing="OnRep_Director", BlueprintReadOnly, Category = "AI|Director")
	TObjectPtr<AActor> Director = nullptr;

	UFUNCTION()
	void OnRep_Director();

#pragma endregion

};
