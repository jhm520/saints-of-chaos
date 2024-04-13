// © 2024 John Henry Miller. All rights reserved

#include "SpringArmComponentBase.h"

#pragma region Framework

USpringArmComponentBase::USpringArmComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	bInterpSpringArmLength = true;
	SpringArmLengthInterpSpeed = 5.0f;
}

void USpringArmComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCurrentSpringArmLength(DeltaTime);
}

void USpringArmComponentBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentSpringArmLength(TargetArmLength);
	SetDesiredSpringArmLength(TargetArmLength);
}


#pragma endregion

#pragma region Spring Arm

void USpringArmComponentBase::SetCurrentSpringArmLength(float NewLength)
{
	CurrentSpringArmLength = NewLength;
	TargetArmLength = NewLength;
}

void USpringArmComponentBase::UpdateCurrentSpringArmLength(const float DeltaTime)
{
	const float NewSpringArmLength = bInterpSpringArmLength ? FMath::FInterpTo(GetCurrentSpringArmLength(), GetDesiredSpringArmLength(), DeltaTime, SpringArmLengthInterpSpeed) : GetDesiredSpringArmLength();
	
	SetCurrentSpringArmLength(NewSpringArmLength);
}

#pragma endregion