#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskDummyMove.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskDummyMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskDummyMove();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ==================================================================
private:
// ==================================================================
private:
};
