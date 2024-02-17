// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AggroSystemComponent.generated.h"

//component for actors that are controlled by the SOCAI system and AI Behaviors
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGGROSYSTEM_API UAggroSystemComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this component's properties
	UAggroSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Aggro System
public:
	UFUNCTION(BlueprintCallable, Category = "Aggro System")
	AActor* FindAggroTarget();
	
	UFUNCTION(BlueprintCallable, Category = "Aggro System")
	AActor* FindClosestTarget();

	UFUNCTION(BlueprintCallable, Category = "Aggro System")
	void FindTargets(TArray<AActor*>& OutTargets);

	UFUNCTION(BlueprintPure, Category = "Aggro System")
	bool ShouldAggro(AActor* AggroTarget);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aggro System")
	float AggroRadius = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aggro System")
	TArray<TEnumAsByte<EObjectTypeQuery>> AggroObjectTypes;


#pragma endregion

#pragma region Threat

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Threat")
	TMap<AActor*, int32> ThreatMap;
public:

	//adds threat to the target
	UFUNCTION(BlueprintCallable, Category = "Threat")
	void AddThreat(AActor* ThreatTarget, int32 ThreatValue);

	//removes threat from the target
	UFUNCTION(BlueprintCallable, Category = "Threat")
	void ClearThreat(AActor* ThreatTarget);

	//returns true if the target threatens the owner of this component
	//OutThreat will be set to the threat value
	UFUNCTION(BlueprintPure, Category = "Threat")
	bool GetThreat(AActor* ThreatTarget, int32& OutThreat) const;

#pragma endregion

};
