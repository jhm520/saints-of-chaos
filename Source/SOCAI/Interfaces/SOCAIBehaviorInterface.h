// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SOCAI/Behavior/SOCAIBehavior.h"
#include "SOCAIBehaviorInterface.generated.h"

class USOCAIBehaviorComponent;
class USOCAIAvatarComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USOCAIBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/** Interface for the owning actor of an SOCAIBehaviorComponent
 * 
 */
class SOCAI_API ISOCAIBehaviorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual USOCAIBehaviorComponent* GetBehaviorComponent() const = 0;
	
	virtual const AActor* GetAvatarActor() const = 0;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "SOCAI", meta=(DisplayName="Do AI Action"))
	void DoAIAction(const FSOCAIAction& Action);

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "SOCAI", meta=(DisplayName="On Entered Behavior"))
	void OnEnteredBehavior(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly, Category = "SOCAI", meta=(DisplayName="On Exited Behavior"))
	void OnExitedBehavior(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const;

};
