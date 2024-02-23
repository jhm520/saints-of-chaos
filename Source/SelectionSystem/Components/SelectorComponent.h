// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectorComponent.generated.h"


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

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Selection")
	TArray<USelectableComponent*> SelectedComponents;
public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Selection")
	void Select(USelectableComponent* SelectableComponent);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Selection")
	void Deselect(USelectableComponent* SelectableComponent);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Selection")
	void ClearSelection();

	UFUNCTION(BlueprintPure, Category = "Selection")
	TArray<USelectableComponent*> GetSelectedComponents() const {return SelectedComponents;};

	
#pragma endregion
};
