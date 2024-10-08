// © 2024 John Henry Miller. All rights reserved


#include "MinimapViewComponent.h"
#include "MinimapSystem/Widgets/MinimapWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UMinimapViewComponent::UMinimapViewComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMinimapViewComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = Cast<APawn>(GetOwner());

	if (!Pawn)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (!PlayerController)
	{
		return;
	}
	
	MinimapWidget = CreateWidget<UMinimapWidget>(PlayerController, MinimapWidgetClass);

	MinimapWidget->AddToViewport();
	// ...
}


// Called every frame
void UMinimapViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

