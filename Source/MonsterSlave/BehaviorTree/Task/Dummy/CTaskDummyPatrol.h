#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskDummyPatrol.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskDummyPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskDummyPatrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ==================================================================
private:
// ==================================================================
private:
	FNavLocation NextLocation;
	EPathFollowingRequestResult::Type Result;
};
