#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Navigation/PathFollowingComponent.h"
#include "CTaskPatrol.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskPatrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ============================================================================
private:
// ============================================================================
private:
	FNavLocation NextLocation;
	EPathFollowingRequestResult::Type Result;
};
