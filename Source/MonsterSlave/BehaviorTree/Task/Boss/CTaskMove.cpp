#include "CTaskMove.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

#include "Global.h"

UCTaskMove::UCTaskMove()
{
	NodeName = "Move";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNullResult(boss, EBTNodeResult::Failed);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNullResult(behaviorComp, EBTNodeResult::Failed);

	controller->MoveToActor(Cast<AActor>(behaviorComp->GetPlayerKey()));

	return EBTNodeResult::Succeeded;
}

void UCTaskMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
