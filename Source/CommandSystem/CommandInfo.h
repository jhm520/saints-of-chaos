// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CommandInfo.generated.h"

class UCommandableComponent;
/**
 * 
 */
UCLASS()
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
	
	virtual bool CheckCommandFinished(UCommandableComponent* Commandable, const FCommandInstance& Command) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Check Command Finished", Category = Command))
	bool K2_CheckCommandFinished(UCommandableComponent* Commandable, const FCommandInstance& Command) const;

#pragma endregion
	
};
