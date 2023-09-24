#include "BehaviorTree/Task/CTaskRotate.h"

#include "Global.h"

UCTaskRotate::UCTaskRotate()
{
	NodeName = "Rotate";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UCTaskRotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
