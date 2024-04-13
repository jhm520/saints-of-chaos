// © 2024 John Henry Miller. All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SOCHUD.generated.h"

/**
 * 
 */
UCLASS()
class SOC_API ASOCHUD : public AHUD
{
	GENERATED_BODY()
friend class ASOCPlayerController;
#pragma region Framework

	virtual void Reset() override;

#pragma endregion

#pragma region Box Select
protected:
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Box Select")
	UBoxSelectWidget* BoxSelectWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "Box Select")
	void SetBoxSelectWidget(UBoxSelectWidget* NewBoxSelectWidget) {BoxSelectWidget = NewBoxSelectWidget;}

	UFUNCTION(BlueprintCallable, Category = "Box Select")
	UBoxSelectWidget* GetBoxSelectWidget() const {return BoxSelectWidget;}

#pragma endregion
	
#pragma region Ready Check
protected:
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Box Select")
	UReadyCheckWidget* ReadyCheckWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "Box Select")
	void SetReadyCheckWidget(UReadyCheckWidget* NewReadyCheckWidget) {ReadyCheckWidget = NewReadyCheckWidget;}

	UFUNCTION(BlueprintCallable, Category = "Box Select")
	UReadyCheckWidget* GetReadyCheckWidget() const {return ReadyCheckWidget;}

#pragma endregion


#pragma region Rematch Check
protected:
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Box Select")
	UReadyCheckWidget* RematchCheckWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "Box Select")
	void SetRematchCheckWidget(UReadyCheckWidget* NewRematchCheckWidget) {RematchCheckWidget = NewRematchCheckWidget;}

	UFUNCTION(BlueprintCallable, Category = "Box Select")
	UReadyCheckWidget* GetRematchCheckWidget() const {return RematchCheckWidget;}

#pragma endregion
	
};
