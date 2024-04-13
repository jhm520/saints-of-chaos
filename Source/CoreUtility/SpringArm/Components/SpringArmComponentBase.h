// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpringArmComponentBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent))
class COREUTILITY_API USpringArmComponentBase : public USpringArmComponent
{
	GENERATED_BODY()

#pragma region Framework
protected:
	USpringArmComponentBase();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;
#pragma endregion

#pragma region Spring Arm

protected:
	UPROPERTY(Transient)
	float CurrentSpringArmLength;

	UPROPERTY(Transient)
	float DesiredSpringArmLength;

	void UpdateCurrentSpringArmLength(const float DeltaTime);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spring Arm")
	bool bInterpSpringArmLength;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spring Arm")
	float SpringArmLengthInterpSpeed;

public:

	UFUNCTION(BlueprintCallable, Category = "Spring Arm")
	void SetCurrentSpringArmLength(float NewLength);

	UFUNCTION(BlueprintCallable, Category = "Spring Arm")
	float GetCurrentSpringArmLength() const { return CurrentSpringArmLength; };

	UFUNCTION(BlueprintCallable, Category = "Spring Arm")
	void SetDesiredSpringArmLength(float NewLength) { DesiredSpringArmLength = NewLength; };

	UFUNCTION(BlueprintCallable, Category = "Spring Arm")
	float GetDesiredSpringArmLength() const { return DesiredSpringArmLength; };

#pragma endregion
	
	
};
