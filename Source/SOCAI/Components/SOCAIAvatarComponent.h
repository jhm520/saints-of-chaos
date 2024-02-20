// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIAvatarComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOCAI_API USOCAIAvatarComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class USOCAIBehaviorComponent;
#pragma region Framework
public:	
	// Sets default values for this component's properties
	USOCAIAvatarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Action
protected:
	UFUNCTION(BlueprintCallable, Category = "AI|Behavior")
	void SetCurrentAction(const FSOCAIAction& InAction);
	
	UPROPERTY(Transient, BlueprintReadOnly, ReplicatedUsing = "OnRep_CurrentAction", Category = "AI|Behavior")
	FSOCAIAction CurrentAction;

	UFUNCTION()
	void OnRep_CurrentAction(const FSOCAIAction& PreviousAction);

	virtual void OnActionChanged(const FSOCAIAction& InCurrentAction, const FSOCAIAction& InPreviousAction);

#pragma endregion

};
