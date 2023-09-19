#include "BehaviorTree/Task/CTaskPhaseChange.h"

#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"
#include "Component/CStateComponent.h"

#include "Global.h"

EBTNodeResult::Type UCTaskPhaseChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = Cast<ACBossController>(OwnerComp.GetOwner());
	OwnerBoss = Controller->GetPossessedBoss();
	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(OwnerBoss);

	if (stateComp->IsIdle() == false)
	{
		return EBTNodeResult::Failed;
	}

	OwnerBoss->ChangePhase();

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UCTaskPhaseChange::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	return EBTNodeResult::Aborted;
}

void UCTaskPhaseChange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	return;
}

void UCTaskPhaseChange::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{

	return;
}