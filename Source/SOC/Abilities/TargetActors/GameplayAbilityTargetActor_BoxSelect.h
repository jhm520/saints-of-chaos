// Fill out your copyright notice in the Description page of Project Settings.

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
	
	void StartBoxSelect();

	void EndBoxSelect();

	void GetTargetActors(TArray<AActor*>& Actors);

	virtual void ConfirmTargetingAndContinue() override;

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
