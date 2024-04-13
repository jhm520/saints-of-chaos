// © 2024 John Henry Miller. All rights reserved

#include "SOCAICharacter.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SOCAI/SOCAIFunctionLibrary.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"
#include "CommandSystem/Components/CommandableComponent.h"

// Sets default values
ASOCAICharacter::ASOCAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 100.0f;

	BehaviorComponent = CreateDefaultSubobject<USOCAIBehaviorComponent>(TEXT("BehaviorComponent"));
	CommandableComponent = CreateDefaultSubobject<UCommandableComponent>(TEXT("CommandableComponent"));
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

	USOCAIBehaviorComponent* LocalBehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!LocalBehaviorComponent)
	{
		return;
	}

	//set the previous owner to be the director of the behavior component
	LocalBehaviorComponent->SetDirector(LocalDirectorController->GetPawn());
}

void ASOCAICharacter::Reset()
{
	Super::Reset();

	Destroy();
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

void ASOCAICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


#pragma region Attitude System
EAttitude ASOCAICharacter::GetAttitudeTowards_Implementation(AActor* Other) const
{
	if (!Other)
	{
		return EAttitude::Neutral;
	}
	

	AActor* Director = GetBehaviorComponent()->GetDirector();

	if (!Director)
	{
		return EAttitude::Neutral;
	}

	const bool bIsDirectedByMyDirector = USOCAIFunctionLibrary::IsActorDirectedBy(Other, Director);

	if (bIsDirectedByMyDirector)
	{
		return EAttitude::Friendly;
	}

	return EAttitude::Hostile;
}
#pragma endregion

#pragma region Behavior

void ASOCAICharacter::OnEnteredBehavior_Implementation(const FSOCAIAction& InEnteredBehaviorAction, const FSOCAIAction& InExitedBehaviorAction) const
{
	if (InEnteredBehaviorAction.ActionTag == SOCAIActionTags::Attack)
	{
		
	}
}

void ASOCAICharacter::DoAIAction_Implementation(const FSOCAIAction& Action)
{
	if (GetController() && GetController()->Implements<USOCAIBehaviorInterface>())
	{
		ISOCAIBehaviorInterface::Execute_DoAIAction(GetController(), Action);
	}
}

void ASOCAICharacter::OnExitedBehavior_Implementation(const FSOCAIAction& InExitedBehaviorAction, const FSOCAIAction& InEnteredBehaviorAction) const
{
	
}

void ASOCAICharacter::OnDirectorPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	BehaviorComponent->InitBehaviorSystem(NewPawn);
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

	//check if we have a current command with a valid target actor, use that one if we do
	FCommandInstance CurrentCommand;
	UCommandSystemBlueprintLibrary::GetCurrentCommand(this, CurrentCommand);

	if (CurrentCommand.IsValid() && CurrentCommand.TargetActor)
	{
		return CurrentCommand.TargetActor;
	}

	//otherwise get the target actor from the behavior component
	ISOCAIBehaviorInterface* BehaviorInterface = Cast<ISOCAIBehaviorInterface>(GetController());

	if (!BehaviorInterface)
	{
		return nullptr;
	}

	USOCAIBehaviorComponent* LocalBehaviorComponent = BehaviorInterface->GetBehaviorComponent();

	if (!LocalBehaviorComponent)
	{
		return nullptr;
	}

	const FSOCAIAction& CurrentAction = LocalBehaviorComponent->GetCurrentAction();

	return CurrentAction.TargetActor;
}

#pragma endregion

#pragma region Command

void ASOCAICharacter::OnCommandBegin_Implementation(const FCommandInstance& Command)
{
	
}

bool ASOCAICharacter::CheckCommandFinished_Implementation(const FCommandInstance& Command) const
{
	return false;
}

#pragma endregion

#pragma region Damage Causer Interface
	
AController* ASOCAICharacter::GetDamageInstigatorController() const
{
	USOCAIBehaviorComponent* LocalBehaviorComponent = GetBehaviorComponent();

	if (!LocalBehaviorComponent)
	{
		return nullptr;
	}

	AActor* Director = LocalBehaviorComponent->GetDirector();

	if (!Director)
	{
		return nullptr;
	}

	AController* InstigatorController = Cast<AController>(Director);

	if (!InstigatorController)
	{
		InstigatorController = Cast<AController>(Director->GetOwner());
	}

	return InstigatorController;
}

#pragma endregion