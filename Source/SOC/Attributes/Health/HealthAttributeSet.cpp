// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"

#include "HealthInterface.h"
#include "Net/UnrealNetwork.h"


UHealthAttributeSet::UHealthAttributeSet()
{
	Health = 100.0f;
	MaxHealth = 100.0f;
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	AActor* OwningActor = GetOwningActor();
	
	if (!OwningActor || !OwningActor->Implements<UHealthInterface>())
	{
		return;
	}

	IHealthInterface::Execute_OnHealthChanged(OwningActor, OldValue, Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
}

bool UHealthAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldHealth);

	AActor* OwningActor = GetOwningActor();
	
	if (!OwningActor || !OwningActor->Implements<UHealthInterface>())
	{
		return;
	}

	IHealthInterface::Execute_OnHealthChanged(OwningActor, OldHealth.GetCurrentValue(), Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaxHealth, OldMaxHealth);

	AActor* OwningActor = GetOwningActor();
	
	if (!OwningActor || !OwningActor->Implements<UHealthInterface>())
	{
		return;
	}

	IHealthInterface::Execute_OnMaxHealthChanged(OwningActor, OldMaxHealth.GetCurrentValue(), MaxHealth.GetCurrentValue(), Health.GetCurrentValue());
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

}