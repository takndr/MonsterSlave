#include "BehaviorTree/Task/Dummy/CTaskDummyMove.h"

#include "Component/CBehaviorComponent.h"
#include "Component/CStateComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Enemy/CDummyController.h"

#include "Global.h"

UCTaskDummyMove::UCTaskDummyMove()
{
	NodeName = "Move";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskDummyMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	return EBTNodeResult::InProgress;
}

void UCTaskDummyMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	CheckNull(player);

	controller->MoveToActor(player);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}