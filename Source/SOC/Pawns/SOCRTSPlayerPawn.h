// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "CommandSystem/Interfaces/CommandInterface.h"
#include "RTSUtility/Pawns/RTSPlayerPawn.h"
#include "SelectionSystem/Interfaces/SelectorInterface.h"
#include "SOCRTSPlayerPawn.generated.h"

class USelectorComponent;
class UGameplayAbilityCollection;
class UCOmmandComponent;
/**
 * 
 */
UCLASS()
class SOC_API ASOCRTSPlayerPawn : public ARTSPlayerPawn, public IAbilitySystemInterface, public ISelectorInterface, public ICommandInterface
{
	GENERATED_BODY()
#pragma region Framework
public:
	// Sets default values for this pawn's properties
	ASOCRTSPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;


#pragma endregion

#pragma region Gameplay Abilities
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TObjectPtr<UGameplayAbilityCollection>> AbilityCollections;

	UFUNCTION()
	void InitAbilitySystem();
	
#pragma endregion
	
#pragma region Selection System

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<USelectorComponent> SelectorComponent;

public:

	virtual USelectorComponent* GetSelectorComponent() const override{return SelectorComponent;};

#pragma endregion

#pragma region Attitude System
public:
	virtual EAttitude GetAttitudeTowards_Implementation(AActor* Other) const override;
#pragma endregion
	
#pragma region Command

protected:
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Behavior")
	TObjectPtr<UCommandComponent> CommandComponent;
public:
	virtual UCommandComponent* GetCommandComponent() const override {return CommandComponent;};

#pragma endregion
};
