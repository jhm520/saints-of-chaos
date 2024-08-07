// © 2024 John Henry Miller. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinimapViewComponent.generated.h"

class UMinimapWidget;

//added to actors to indicate that this actor is meant to view the minimap
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIMAPSYSTEM_API UMinimapViewComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this component's properties
	UMinimapViewComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion
	
#pragma region Minimap

	UPROPERTY()
	UMinimapWidget* MinimapWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Minimap")
	TSubclassOf<UMinimapWidget> MinimapWidgetClass;
	
#pragma endregion
};
