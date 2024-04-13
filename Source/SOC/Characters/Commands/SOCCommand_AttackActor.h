// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "CommandSystem/CommandInfo.h"
#include "SOCCommand_AttackActor.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API USOCCommand_AttackActor : public UCommandInfo
{
	GENERATED_BODY()

#pragma region Framework

public:
	USOCCommand_AttackActor();
	
#pragma endregion

#pragma region Command
public:

	virtual void OnCommandBegin(const UCommandableComponent* Commandable, const FCommandInstance& Command) const override;

	virtual void OnCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const override;

	virtual void ContinueCommand(float DeltaSeconds, const UCommandableComponent* Commandable, const FCommandInstance& Command) const override;

	virtual bool CheckCommandFinished(const UCommandableComponent* Commandable, const FCommandInstance& Command) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	float AcceptanceRadius = 150.0f;
#pragma endregion

	
};
