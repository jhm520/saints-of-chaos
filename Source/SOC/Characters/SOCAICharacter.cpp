// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAICharacter.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"
#include "SOCAI/Components/SOCAIAvatarComponent.h"

// Sets default values
ASOCAICharacter::ASOCAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100.0f;

	AvatarComponent = CreateDefaultSubobject<USOCAIAvatarComponent>(TEXT("AvatarComponent"));
}

// Called when the game starts or when spawned
void ASOCAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOCAICharacter::SetOwner( AActor* NewOwner )
{
	Super::SetOwner(NewOwner);
}

void ASOCAICharacter::SpawnDefaultController()
{
	//before we spawn the AI controller, we see if we already set a different owner of this actor
	//if so, we take that owner and set it to be the director of the behavior component
	
	AActor* OldOwner = GetOwner();

	AController* LocalDirectorController = Cast<AController>(OldOwner);

	if (!LocalDirectorController)
	{
		return;
	}

	LocalDirectorController->OnPossessedPawnChanged.AddDynamic(this, &ASOCAICharacter::OnDirectorPossessedPawnChanged);
	
	Super::SpawnDefaultController();

	AController* LocalController = GetController();

	if (!LocalController)
	{
		return;
	}

	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(LocalController);

	if (!BehaviorInterface)
	{
		return;
	}

	USOCAIBehaviorComponent* BehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!BehaviorComponent)
	{
		return;
	}
	
	//set the previous owner to be the director of the behavior component
	BehaviorComponent->SetDirector(OldOwner);

	BehaviorComponent->SetDirectorPawn(LocalDirectorController->GetPawn());
}

// Called every frame
void ASOCAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASOCAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region Attitude System
EAttitude ASOCAICharacter::GetAttitudeTowards_Implementation(AActor* Other) const
{
	if (!Other)
	{
		return EAttitude::Neutral;
	}

	if (!GetAvatarComponent())
	{
		return EAttitude::Neutral;
	}

	APawn* DirectorPawn = GetAvatarComponent()->GetDirectorPawn();

	if (!DirectorPawn)
	{
		return EAttitude::Neutral;
	}

	if (!DirectorPawn->Implements<UAttitudeInterface>())
	{
		return EAttitude::Neutral;
	}

	return IAttitudeInterface::Execute_GetAttitudeTowards(DirectorPawn, Other);
}
#pragma endregion

#pragma region Behavior

USOCAIBehaviorComponent* ASOCAICharacter::GetBehaviorComponent() const
{
	ISOCAIBehaviorInterface* ControllerBehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetController());

	if (!ControllerBehaviorInterface)
	{
		return nullptr;
	}

	return ControllerBehaviorInterface->GetBehaviorComponent();
}

USOCAIAvatarComponent* ASOCAICharacter::GetAvatarComponent() const
{
	return AvatarComponent;
}

void ASOCAICharacter::OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const
{
	if (InEnteredBehaviorAction.ActionTag == SOCAIActionTags::Attack)
	{
		
	}
}

void ASOCAICharacter::OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const
{
	
}

void ASOCAICharacter::OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (!NewPawn)
	{
		return;
	}
	
	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(this);

	if (!BehaviorInterface)
	{
		return;
	}

	USOCAIBehaviorComponent* BehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!BehaviorComponent)
	{
		return;
	}

	AActor* Director = BehaviorComponent->GetDirector();

	if (!Director)
	{
		return;
	}
	
	AController* LocalDirectorController = Cast<AController>(Director);

	if (!LocalDirectorController)
	{
		return;
	}
	
	BehaviorComponent->SetDirectorPawn(LocalDirectorController->GetPawn());
}


#pragma endregion

#pragma region Target Actors
	
/** Returns the actor that is the target of this ability */
AActor* ASOCAICharacter::GetTargetActor() const
{
	if (!GetController())
	{
		return nullptr;
	}

	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetController());

	if (!BehaviorInterface)
	{
		return nullptr;
	}

	USOCAIBehaviorComponent* BehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!BehaviorComponent)
	{
		return nullptr;
	}

	const FSOCAIAction& CurrentAction = BehaviorComponent->GetCurrentAction();

	return CurrentAction.TargetActor;
}

#pragma endregion