// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickableActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COREUTILITY_API UClickableActorComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UClickingComponent;
	
#pragma region Framework
	
public:	
	// Sets default values for this component's properties
	UClickableActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Clickable

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Clicking")
	bool bIsClickable;

	void SetupClickable();

	UFUNCTION()
	void OnActorClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

#pragma endregion
	
};
