// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_BoxSelect.generated.h"

class UBoxSelectWidget;
/**
 * 
 */
UCLASS()
class SOC_API AGameplayAbilityTargetActor_BoxSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
protected:
	
	AGameplayAbilityTargetActor_BoxSelect();
	
	FGameplayAbilityTargetDataHandle MakeTargetData(TArray<AActor*> TargetActors) const;

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	void CreateBoxSelectWidget();
	
	void DestroyBoxSelectWidget();
	
	void GetBoxSelectStartPoint();

	void GetBoxSelectEndPoint();

	void GetTargetActors(TArray<AActor*>& Actors);

	virtual void ConfirmTargetingAndContinue() override;

	virtual void Tick(float DeltaSeconds) override;

#pragma region Box Select
protected:

	UPROPERTY()
	FVector2D BoxSelectStartPosition;

	UPROPERTY()
	FHitResult BoxSelectStartHitResult;

	UPROPERTY()
	FVector2D BoxSelectEndPosition;

	UPROPERTY()
	FHitResult BoxSelectEndHitResult;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Box Select")
	TSubclassOf<UBoxSelectWidget> BoxSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Box Select")
	TEnumAsByte<ETraceTypeQuery> ClickTraceType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Box Select")
	TEnumAsByte<ETraceTypeQuery> SelectBoxTraceType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Box Select")
	bool bTraceComplex;
	
	UPROPERTY(BlueprintReadWrite, Category = "Box Select")
	UBoxSelectWidget* BoxSelectWidget;

#pragma endregion

};
