// Fill out your copyright notice in the Description page of Project Settings.


#include "SOCAICharacter.h"

#include "AIController.h"
#include "SOCAI/Components/SOCAIBehaviorComponent.h"

// Sets default values
ASOCAICharacter::ASOCAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

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

UE_DISABLE_OPTIMIZATION
void ASOCAICharacter::SpawnDefaultController()
{
	//before we spawn the AI controller, we see if we already set a different owner of this actor
	//if so, we take that owner and set it to be the director of the behavior component
	
	AActor* OldOwner = GetOwner();
	
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
}
UE_ENABLE_OPTIMIZATION

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