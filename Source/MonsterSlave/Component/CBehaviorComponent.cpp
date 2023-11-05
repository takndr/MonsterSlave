#include "Component/CBehaviorComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Player/CPlayer.h"

#include "Global.h"

UCBehaviorComponent::UCBehaviorComponent()
{

}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCBehaviorComponent::SetWaitMode()
{
	Blackboard->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Wait);
}

void UCBehaviorComponent::SetRotateMode()
{
	Blackboard->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Rotate);
}

void UCBehaviorComponent::SetMoveMode()
{
	Blackboard->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Move);
}

void UCBehaviorComponent::SetActionMode()
{
	Blackboard->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	Blackboard->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Patrol);
}

ACPlayer* UCBehaviorComponent::GetPlayerKey()
{
	ACPlayer* player = Cast<ACPlayer>(Blackboard->GetValueAsObject("PlayerKey"));
	return player;
}

FVector UCBehaviorComponent::GetLocationKey()
{
	return Blackboard->GetValueAsVector("LocationKey");
}

EBehaviorType UCBehaviorComponent::GetCurrentBehavior()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum("BehaviorKey");
}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetCurrentBehavior() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsRotateMode()
{
	return GetCurrentBehavior() == EBehaviorType::Rotate;
}

bool UCBehaviorComponent::IsMoveMode()
{
	return GetCurrentBehavior() == EBehaviorType::Move;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetCurrentBehavior() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetCurrentBehavior() == EBehaviorType::Patrol;
}