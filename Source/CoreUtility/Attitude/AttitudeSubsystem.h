#pragma once

#include "CoreMinimal.h"
#include "AttitudeInterface.h"

#include "AttitudeSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttitudeChangedDelegate, AActor*, Actor);

/**
 * This subsystem just keeps a reference to actors that have attitude and broadcasts events when they change.
 */
UCLASS()
class COREUTILITY_API UAttitudeSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	
#pragma region Framework
public:
	UAttitudeSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "Attitude")
	static UAttitudeSubsystem* Get(const UObject* WorldContext);
#pragma endregion

#pragma region Attitude Interface
protected:
	UPROPERTY()
	TArray<AActor*> RegisteredActors;
public:
	UPROPERTY(BlueprintAssignable, Category = "Attitude")
	FOnAttitudeChangedDelegate OnAttitudeChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Attitude")
	void Register(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Attitude")
	void Unregister(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Attitude")
	void AttitudeChanged(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Attitude")
	TArray<AActor*> GetAllActorsWithAttitudeTowards(AActor*Towards, EAttitude Attitude, bool bIncludeChildActors = true);

	UFUNCTION(BlueprintPure, Category = "Attitude")
	TArray<AActor*> GetAllActorsWithAttitudesTowards(AActor*Towards, TSet<EAttitude> Attitudes, bool bIncludeChildActors = true);

	UFUNCTION(BlueprintPure, Category = "Attitude")
	TArray<AActor*> GetAllActorsWithAttitude();
#pragma endregion

	
};
