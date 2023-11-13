#include "BehaviorTree/Task/Dummy/CTaskDummyPatrol.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Component/CStateComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Enemy/CDummyController.h"

#include "Global.h"

UCTaskDummyPatrol::UCTaskDummyPatrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskDummyPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	CheckNullResult(navSystem, EBTNodeResult::Failed);

	while (1)
	{
		if (navSystem->GetRandomReachablePointInRadius(enemy->GetActorLocation(), 500.0f, NextLocation))
		{
			break;
		}
	}
	controller->GetBlackboardComponent()->SetValueAsVector("LocationKey", NextLocation.Location);

	return EBTNodeResult::InProgress;
}

void UCTaskDummyPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNull(enemy);

	Result = controller->MoveToLocation(controller->GetBlackboardComponent()->GetValueAsVector("LocationKey"), 5.0f);

	if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}