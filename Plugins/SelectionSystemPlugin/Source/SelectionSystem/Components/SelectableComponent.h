// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedDelegate, AActor*, Selector);

//this is a component that is meant to be added to actors that are selectable by selectors
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SELECTIONSYSTEM_API USelectableComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Framework

	friend class USelectorComponent;
public:	
	// Sets default values for this component's properties
	USelectableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Selectable

	UFUNCTION()
	void OnSelected(AActor* Selector);

	UPROPERTY(BlueprintAssignable, Category = "Selection")
	FOnSelectedDelegate OnSelectedDelegate;

	UFUNCTION()
	void OnDeselected(AActor* Selector);

	UPROPERTY(BlueprintAssignable, Category = "Selection")
	FOnSelectedDelegate OnDeselectedDelegate;

#pragma endregion


};
