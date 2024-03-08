// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityTargetActor_BoxSelect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbility.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SOC/HUD/Widgets/BoxSelectWidget.h"

UE_DISABLE_OPTIMIZATION
AGameplayAbilityTargetActor_BoxSelect::AGameplayAbilityTargetActor_BoxSelect()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	ShouldProduceTargetDataOnServer = false;
}

FGameplayAbilityTargetDataHandle AGameplayAbilityTargetActor_BoxSelect::MakeTargetData(TArray<AActor*> TargetActors) const
{
	return UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(TargetActors, false);
}

/** Initialize and begin targeting logic  */
void AGameplayAbilityTargetActor_BoxSelect::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	CreateBoxSelectWidget();

	GetBoxSelectStartPoint();
}

void AGameplayAbilityTargetActor_BoxSelect::CreateBoxSelectWidget()
{
	if (!OwningAbility)
	{
		return;
	}
	
	APlayerController* PlayerController = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();

	if (!PlayerController || !PlayerController->IsLocalPlayerController())
	{
		return;
	}

	BoxSelectWidget = CreateWidget<UBoxSelectWidget>(PlayerController, BoxSelectWidgetClass);

	if (!BoxSelectWidget)
	{
		return;
	}

	BoxSelectWidget->AddToViewport();

	BoxSelectWidget->OnBoxSelectInput(true);
}

void AGameplayAbilityTargetActor_BoxSelect::DestroyBoxSelectWidget()
{
	if (!BoxSelectWidget)
	{
		return;
	}

	BoxSelectWidget->OnBoxSelectInput(false);
	BoxSelectWidget->RemoveFromParent();
	BoxSelectWidget = nullptr;
}

void AGameplayAbilityTargetActor_BoxSelect::GetBoxSelectStartPoint()
{
	APlayerController* PlayerController = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();

	if (!PlayerController || !PlayerController->IsLocalPlayerController())
	{
		return;
	}

	float MousePosX;
	float MousePosY;
	
	PlayerController->GetMousePosition(MousePosX, MousePosY);

	FHitResult LocalBoxSelectStartHitResult;

	if (PlayerController->GetHitResultUnderCursorByChannel(ClickTraceType, bTraceComplex, LocalBoxSelectStartHitResult))
	{
		BoxSelectStartHitResult = LocalBoxSelectStartHitResult;
	}
	
	BoxSelectStartPosition = FVector2D(MousePosX, MousePosY);
}

void AGameplayAbilityTargetActor_BoxSelect::GetBoxSelectEndPoint()
{
	APlayerController* PlayerController = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();

	if (!PlayerController || !PlayerController->IsLocalPlayerController())
	{
		return;
	}

	float MousePosX;
	float MousePosY;
	
	PlayerController->GetMousePosition(MousePosX, MousePosY);

	FHitResult LocalBoxSelectEndHitResult;

	if (PlayerController->GetHitResultUnderCursorByChannel(ClickTraceType, bTraceComplex, LocalBoxSelectEndHitResult))
	{
		BoxSelectEndHitResult = LocalBoxSelectEndHitResult;
	}
	
	BoxSelectEndPosition = FVector2D(MousePosX, MousePosY);
}

void AGameplayAbilityTargetActor_BoxSelect::GetTargetActors(TArray<AActor*>& Actors)
{
	APlayerController* PlayerController = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();

	if (!PlayerController || !PlayerController->IsLocalPlayerController())
	{
		return;
	}

	//can't do anything if we don't have valid hit results
	if (!BoxSelectStartHitResult.bBlockingHit || !BoxSelectEndHitResult.bBlockingHit)
	{
		return;
	}

	FVector CameraPosition;
	FRotator CameraRotator;
	PlayerController->GetPlayerViewPoint(CameraPosition, CameraRotator);
	
	//DrawDebugSphere(PlayerController->GetWorld(), BoxSelectStartHitResult.ImpactPoint, 100.0f, 12, FColor::Red, false, 5.0f);
	//DrawDebugSphere(PlayerController->GetWorld(), BoxSelectEndHitResult.ImpactPoint, 100.0f, 12, FColor::Red, false, 5.0f);

	//project the hit results from the Mouse starting positions onto the camera plane
	const FVector& BoxSelectStartCameraPlaneProjected = UKismetMathLibrary::ProjectPointOnToPlane(BoxSelectStartHitResult.ImpactPoint, CameraPosition, CameraRotator.Vector());
	const FVector& BoxSelectEndCameraPlaneProjected = UKismetMathLibrary::ProjectPointOnToPlane(BoxSelectEndHitResult.ImpactPoint, CameraPosition, CameraRotator.Vector());
	
	//DrawDebugSphere(PlayerController->GetWorld(), BoxSelectStartCameraPlaneProjected, 100.0f, 12, FColor::Red, false, 5.0f);
	//DrawDebugSphere(PlayerController->GetWorld(), BoxSelectEndCameraPlaneProjected, 100.0f, 12, FColor::Red, false, 5.0f);

	const static float SelectBoxTraceLength = 25000.0f;

	//find the midpoint of the two hit results
	const FVector& SelectBoxTraceMidpoint = UKismetMathLibrary::VLerp(BoxSelectStartHitResult.ImpactPoint, BoxSelectEndHitResult.ImpactPoint, 0.5f);
	//DrawDebugSphere(PlayerController->GetWorld(), SelectBoxTraceMidpoint, 100.0f, 12, FColor::Red, false, 5.0f);

	//find the midpoint of the two projected hit results projected onto the camera
	const FVector& SelectBoxTraceMidpointCamera = UKismetMathLibrary::VLerp(BoxSelectStartCameraPlaneProjected, BoxSelectEndCameraPlaneProjected, 0.5f);

	//DrawDebugSphere(PlayerController->GetWorld(), SelectBoxTraceMidpointCamera, 100.0f, 12, FColor::Red, false, 5.0f);

	//find the vector between the two midpoints, this will be the direction and orientation of the box trace
	const FVector& TraceDistVector = SelectBoxTraceMidpoint - SelectBoxTraceMidpointCamera;

	//the end location will just go from the midpoint of the camera trace in the direction of the trace vector
	const FVector& SelectBoxTraceEndLocation = SelectBoxTraceMidpointCamera + (TraceDistVector.GetSafeNormal().GetClampedToSize(SelectBoxTraceLength, SelectBoxTraceLength));

	//rotation will be the rotation of the trace vector
	const FRotator& SelectBoxTraceRotation = TraceDistVector.Rotation();

	//half size will be half the distance between the two projected hit results
	const float HalfSizeX = FMath::Abs(BoxSelectStartCameraPlaneProjected.X - BoxSelectEndCameraPlaneProjected.X) / 2.0f;
	const float HalfSizeY = FMath::Abs(BoxSelectStartCameraPlaneProjected.Y - BoxSelectEndCameraPlaneProjected.Y) / 2.0f;

	const FVector& SelectBoxTraceHalfSize = FVector(10.0f, HalfSizeY, HalfSizeX);
	
	TArray<FHitResult> OutHits;
	
	TArray<AActor*> ActorsToIgnore = {};
	const bool bBlockingTrace = UKismetSystemLibrary::BoxTraceMulti(
		OwningAbility->GetCurrentActorInfo()->AvatarActor.Get(),
		SelectBoxTraceMidpointCamera,
		SelectBoxTraceEndLocation,
		SelectBoxTraceHalfSize,
		SelectBoxTraceRotation,
		SelectBoxTraceType,
		bTraceComplex,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		false,
		FLinearColor::Red,
		FLinearColor::Green,
		5.0f
		);
	
	for (FHitResult Hit : OutHits)
	{
		if (Hit.GetActor())
		{
			Actors.AddUnique(Hit.GetActor());
		}
	}
}

void AGameplayAbilityTargetActor_BoxSelect::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	
	GetBoxSelectEndPoint();
	DestroyBoxSelectWidget();
	
	bDebug = false;
	TArray<AActor*> TargetActors;
	GetTargetActors(TargetActors);
	FGameplayAbilityTargetDataHandle Handle = MakeTargetData(TargetActors);
	TargetDataReadyDelegate.Broadcast(Handle);
}

void AGameplayAbilityTargetActor_BoxSelect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetBoxSelectEndPoint();
}


UE_ENABLE_OPTIMIZATION