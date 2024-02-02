#include "AbilityTask_SpawnGameplayActor.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityTask_SpawnGameplayActor)

UAbilityTask_SpawnGameplayActor::UAbilityTask_SpawnGameplayActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

UAbilityTask_SpawnGameplayActor* UAbilityTask_SpawnGameplayActor::SpawnGameplayActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> InClass)
{
	UAbilityTask_SpawnGameplayActor* MyObj = NewAbilityTask<UAbilityTask_SpawnGameplayActor>(OwningAbility);
	MyObj->CachedTargetDataHandle = MoveTemp(TargetData);
	return MyObj;
}

// ---------------------------------------------------------------------------------------

bool UAbilityTask_SpawnGameplayActor::BeginSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> InClass, AActor*& SpawnedActor)
{
	if (Ability && Ability->GetCurrentActorInfo()->IsNetAuthority() && ShouldBroadcastAbilityTaskDelegates())
	{
		UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			const FGameplayAbilityActorInfo &Info = OwningAbility->GetActorInfo();

			SpawnedActor = World->SpawnActorDeferred<AActor>(InClass, FTransform::Identity, Info.OwnerActor.Get(), Cast<APawn>(Info.AvatarActor.Get()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		}
	}
	
	if (SpawnedActor == nullptr)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(nullptr);
		}
		return false;
	}

	return true;
}

void UAbilityTask_SpawnGameplayActor::FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor)
{
	if (SpawnedActor)
	{
		bool bTransformSet = false;
		FTransform SpawnTransform;
		if (FGameplayAbilityTargetData* LocationData = CachedTargetDataHandle.Get(0))		//Hardcode to use data 0. It's OK if data isn't useful/valid.
		{
			//Set location. Rotation is unaffected.
			if (LocationData->HasHitResult())
			{
				SpawnTransform.SetLocation(LocationData->GetHitResult()->Location);
				bTransformSet = true;
			}
			else if (LocationData->HasEndPoint())
			{
				SpawnTransform = LocationData->GetEndPointTransform();
				bTransformSet = true;
			}
		}
		if (!bTransformSet)
		{
			if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
			{
				SpawnTransform = ASC->GetOwner()->GetTransform();
			}
		}

		SpawnedActor->FinishSpawning(SpawnTransform);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			Success.Broadcast(SpawnedActor);
		}
	}

	EndTask();
}
// ---------------------------------------------------------------------------------------


