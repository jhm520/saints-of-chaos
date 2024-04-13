// © 2024 John Henry Miller. All rights reserved

#include "CommandSubsystem.h"
#include "CommandInfo.h"

UCommandSubsystem* UCommandSubsystem::Get(const UObject* WorldContext)
{
	if(!WorldContext)
	{
		return nullptr;
	}
	
	if(const UWorld* World = WorldContext->GetWorld())
	{
		return World->GetSubsystem<UCommandSubsystem>();
	}
	
	return nullptr;
}


void UCommandSubsystem::AddCommand(UCommandInfo* CommandInfo)
{
	CommandMap.Add(CommandInfo->CommandTag, CommandInfo);
}
	
void UCommandSubsystem::RemoveCommand(UCommandInfo* CommandInfo)
{
	CommandMap.Remove(CommandInfo->CommandTag);
}

const UCommandInfo* UCommandSubsystem::GetCommand(const FGameplayTag& CommandTag) const
{
	const TObjectPtr<UCommandInfo>* CommandInfoPtr = CommandMap.Find(CommandTag);

	if (CommandInfoPtr)
	{
		return *CommandInfoPtr;
	}

	return nullptr;
}
