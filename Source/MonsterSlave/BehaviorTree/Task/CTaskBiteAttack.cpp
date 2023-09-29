#include "BehaviorTree/Task/CTaskBiteAttack.h"

#include "Component/CStateComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

#include "Global.h"

UCTaskBiteAttack::UCTaskBiteAttack()
{
	NodeName = "Bite";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskBiteAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	RunningTime = 0.0f;

	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNullResult(boss, EBTNodeResult::Failed);

	boss->BiteAttack();

	return EBTNodeResult::InProgress;
}

void UCTaskBiteAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNull(boss);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(boss);
	CheckNull(stateComp);

	RunningTime += DeltaSeconds;

	if (stateComp->IsIdle() && (RunningTime >= Delay))
	{
		CLog::Print("BiteEnd");
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
