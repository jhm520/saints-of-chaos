//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveAssigneeComponent.generated.h"

class AObjective;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OBJECTIVESYSTEM_API UObjectiveAssigneeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectiveAssigneeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Objective System


#pragma endregion
	
};
