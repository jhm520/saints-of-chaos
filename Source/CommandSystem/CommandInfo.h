// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CommandInfo.generated.h"

class UCommandableComponent;

UENUM(BlueprintType)
enum class ECommandTriggerMode : uint8
{
	//The trigger will fire when the command begins
	OnBegin,
	//The rigger will fire when the command is complete
	OnComplete,
	None
};

//struct containing information about an animation instance to be applied to the AI character when this behavior is active
USTRUCT(BlueprintType)
struct COMMANDSYSTEM_API FCommandAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	ECommandTriggerMode ActivationMode = ECommandTriggerMode::OnBegin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	ECommandTriggerMode DeactivationMode = ECommandTriggerMode::OnComplete;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	TSubclassOf<UAnimInstance> AnimInstanceClass;
};
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, ClassGroup = (CommandSystem))
class COMMANDSYSTEM_API UCommandInfo : public UDataAsset
{
	GENERATED_BODY()

#pragma region Framework

	virtual void PostLoad() override;
	
	virtual void PostInitProperties() override;

	virtual void BeginDestroy() override;

#pragma endregion

	
#pragma region Command
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	FGameplayTag CommandTag = FGameplayTag::EmptyTag;

	virtual void OnCommandBegin(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

	virtual void OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

	virtual bool CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Check Command Finished", Category = Command))
	bool K2_CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

#pragma endregion

#pragma region Animation
protected:
	
	// Linked animation instance to be applied to the AI character when this behavior is active
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TArray<FCommandAnimInstance> CommandAnimInstances;

	virtual void OnBegin_AnimInstances(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

	virtual void OnComplete_AnimInstances(const UCommandableComponent* Commandable, const FCommandInstance& Command) const;

#pragma endregion
	
};
