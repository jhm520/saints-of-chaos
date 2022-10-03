#include "SOCAIGameplayTags.h"

namespace SOCAIBehaviorTags
{
	UE_DEFINE_GAMEPLAY_TAG(Behavior,					TEXT("SOCAI.Behavior"))
	UE_DEFINE_GAMEPLAY_TAG(Idle,						TEXT("SOCAI.Behavior.Idle"))
	UE_DEFINE_GAMEPLAY_TAG(FindEnemy,					TEXT("SOCAI.Behavior.FindEnemy"))
	UE_DEFINE_GAMEPLAY_TAG(CallForBackup,				TEXT("SOCAI.Behavior.FindEnemy.CallForBackup"))
	UE_DEFINE_GAMEPLAY_TAG(MoveToAllies,				TEXT("SOCAI.Behavior.FindEnemy.CallForBackup.MoveToAllies"))
	UE_DEFINE_GAMEPLAY_TAG(RaiseAlarm,					TEXT("SOCAI.Behavior.FindEnemy.CallForBackup.RaiseAlarm"))
	UE_DEFINE_GAMEPLAY_TAG(EngageEnemy,					TEXT("SOCAI.Behavior.FindEnemy.EngageEnemy"))
	UE_DEFINE_GAMEPLAY_TAG(MoveToCombatRange,			TEXT("SOCAI.Behavior.FindEnemy.EngageEnemy.MoveToCombatRange"))
	UE_DEFINE_GAMEPLAY_TAG(Attack,						TEXT("SOCAI.Behavior.FindEnemy.EngageEnemy.Attack"))
	UE_DEFINE_GAMEPLAY_TAG(Disengage,					TEXT("SOCAI.Behavior.FindEnemy.Disengage"))
	UE_DEFINE_GAMEPLAY_TAG(Retreat,						TEXT("SOCAI.Behavior.FindEnemy.Disengage.Retreat"))
	UE_DEFINE_GAMEPLAY_TAG(MoveToSafeLocation,			TEXT("SOCAI.Behavior.FindEnemy.Disengage.Retreat.MoveToSafeLocation"))
	UE_DEFINE_GAMEPLAY_TAG(Surrender,					TEXT("SOCAI.Behavior.FindEnemy.Disengage.Surrender"))
	UE_DEFINE_GAMEPLAY_TAG(InvestigateLastKnownEnemy,	TEXT("SOCAI.Behavior.InvestigateLastKnownEnemy"))
	UE_DEFINE_GAMEPLAY_TAG(GoToEnemyLastKnownLocation,	TEXT("SOCAI.Behavior.InvestigateLastKnownEnemy.GoToEnemyLastKnownLocation"))
	UE_DEFINE_GAMEPLAY_TAG(SearchArea,					TEXT("SOCAI.Behavior.InvestigateLastKnownEnemy.SearchArea"))
	UE_DEFINE_GAMEPLAY_TAG(AllClear,					TEXT("SOCAI.Behavior.InvestigateLastKnownEnemy.AllClear"))
	UE_DEFINE_GAMEPLAY_TAG(FollowSchedule,				TEXT("SOCAI.Behavior.FollowSchedule"))
	UE_DEFINE_GAMEPLAY_TAG(LookUpNextTask,				TEXT("SOCAI.Behavior.FollowSchedule.LookUpNextTask"))
	UE_DEFINE_GAMEPLAY_TAG(FollowPathToTaskLocation,	TEXT("SOCAI.Behavior.FollowSchedule.FollowPathToTaskLocation"))
	UE_DEFINE_GAMEPLAY_TAG(DoTask,						TEXT("SOCAI.Behavior.FollowSchedule.DoTask"))
	
}