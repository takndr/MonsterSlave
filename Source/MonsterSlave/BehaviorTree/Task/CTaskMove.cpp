#include "BehaviorTree/Task/CTaskMove.h"

#include "Global.h"

UCTaskMove::UCTaskMove()
{
	NodeName = "Move";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UCTaskMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
