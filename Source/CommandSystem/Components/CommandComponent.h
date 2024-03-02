// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandComponent.generated.h"

class UCommandInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMANDSYSTEM_API UCommandComponent : public UActorComponent
{
	GENERATED_BODY()
#pragma region Framework
public:	
	// Sets default values for this component's properties
	UCommandComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Command

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Category = "Command")
	bool Command(UCommandableComponent* Commandable, const FCommandInstance& Command, bool bQueue = false);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Command")
	TArray<TObjectPtr<UCommandInfo>> CommandInfos;
#pragma endregion
		
};
