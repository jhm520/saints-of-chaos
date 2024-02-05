#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

UINTERFACE(BlueprintType)
class SOC_API UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Health Interface that provides getters / setters for health management
 * Actors that implement this interface expected to have health and can take damage
 */
class SOC_API IHealthInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Health")
	float GetHealth() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Health")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintAuthorityOnly, Category="Health")
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintAuthorityOnly, Category="Health")
	void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Health")
	void OnHealthChanged(float OldHealth, float NewHealth, float MaxHealth);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Health")
	void OnMaxHealthChanged(float OldMaxHealth, float MaxHealth, float CurrentHealth);

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Health")
	bool IsAlive() const;
};
