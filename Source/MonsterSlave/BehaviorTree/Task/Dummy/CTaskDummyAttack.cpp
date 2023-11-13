#include "BehaviorTree/Task/Dummy/CTaskDummyAttack.h"

#include "Component/CStateComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Enemy/CDummyController.h"

#include "Global.h"

UCTaskDummyAttack::UCTaskDummyAttack()
{
	NodeName = "Attack";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskDummyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	RunningTime = 0.0f;

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);
	enemy->Attack();

	return EBTNodeResult::InProgress;
}

void UCTaskDummyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	RunningTime += DeltaSeconds;

	// TODO : 모션이 끝나고 딜레이 시간 적용되게 설정해야 할 듯

	if (stateComp->IsIdle() && (RunningTime >= Delay))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}