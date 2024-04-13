// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_InstantCursor.generated.h"

/**
 * 
 */
UCLASS()
class GASUTILITY_API AGameplayAbilityTargetActor_InstantCursor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
protected:

#pragma region Framework

	AGameplayAbilityTargetActor_InstantCursor();
	
	FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& HitResult) const;
	
	virtual void ConfirmTargetingAndContinue() override;

#pragma endregion

#pragma region Cursor Trace
	UFUNCTION(BlueprintNativeEvent)
	FHitResult PerformTrace();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	TEnumAsByte<ETraceTypeQuery> CursorTraceChannel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn))
	bool bTraceComplex;

#pragma endregion

};
