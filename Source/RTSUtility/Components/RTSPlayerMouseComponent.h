// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSPlayerMouseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMouseScreenEdgeScrollDelegate, const FVector2D&, Direction);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTSUTILITY_API URTSPlayerMouseComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region Framework
public:	
	// Sets default values for this component's properties
	URTSPlayerMouseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma endregion

#pragma region Mouse

	UFUNCTION(BlueprintCallable, Category = "Mouse")
	void SetRTSMouseEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "Mouse")
	bool IsRTSMouseEnabled() const { return bRTSMouseEnabled; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse")
	bool bRTSMouseEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mouse")
	bool bRTSMouseEnabledByDefault;

#pragma endregion

#pragma region Controller

	//get the player controller responsible for moving this mouse
	UFUNCTION(BlueprintPure, Category = "Controller")
	APlayerController* GetMouseController() const;

#pragma endregion

#pragma region Scrolling

protected:
	//get the player controller responsible for moving this mouse
	void CheckMouseScrolling();

	//how close the mouse has to be to the edge of the screen to start scrolling
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scrolling")
	float MouseScrollBorder = 10.0f;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMouseScreenEdgeScrollDelegate OnMouseScreenEdgeScroll;

#pragma endregion

};
