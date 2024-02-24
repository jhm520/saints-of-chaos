// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectorComponent.generated.h"

class USelectableComponent;


//this is a component that is meant to be added to actors that care about selecting things

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELECTIONSYSTEM_API USelectorComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Framework

public:	
	// Sets default values for this component's properties
	USelectorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Selection
protected:

	UPROPERTY(Transient, ReplicatedUsing="OnRep_SelectedComponents", BlueprintReadOnly, Category = "Selection")
	TArray<USelectableComponent*> SelectedComponents;

	UFUNCTION()
	void OnRep_SelectedComponents(const TArray<USelectableComponent*>& OldSelectedComponents);

	UFUNCTION(Server, Reliable)
	void ServerSelect(USelectableComponent* SelectableComponent);

	UFUNCTION(Server, Reliable)
	void ServerDeselect(USelectableComponent* SelectableComponent);

	UFUNCTION(Server, Reliable)
	void ServerClearSelection();
	
public:

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void Select(USelectableComponent* SelectableComponent, bool bRepToServer = true);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void Deselect(USelectableComponent* SelectableComponent, bool bRepToServer = true);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Selection")
	void ClearSelection(bool bRepToServer = true);

	UFUNCTION(BlueprintPure, Category = "Selection")
	TArray<USelectableComponent*> GetSelectedComponents() const {return SelectedComponents;};

	
#pragma endregion
};
