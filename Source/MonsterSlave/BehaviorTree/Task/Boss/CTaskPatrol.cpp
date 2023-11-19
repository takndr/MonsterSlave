#include "BehaviorTree/Task/Boss/CTaskPatrol.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Component/CStateComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

#include "Global.h"

UCTaskPatrol::UCTaskPatrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNullResult(boss, EBTNodeResult::Failed);

	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	CheckNullResult(navSystem, EBTNodeResult::Failed);

	while (1)
	{
		if (navSystem->GetRandomReachablePointInRadius(boss->GetActorLocation(), 500.0f, NextLocation))
		{
			break;
		}
	}
	controller->GetBlackboardComponent()->SetValueAsVector("LocationKey", NextLocation.Location);

	return EBTNodeResult::InProgress;
}

void UCTaskPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNull(boss);

	Result = controller->MoveToLocation(controller->GetBlackboardComponent()->GetValueAsVector("LocationKey"), 5.0f);

	if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
}