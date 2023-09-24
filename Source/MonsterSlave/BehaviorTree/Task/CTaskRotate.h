#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskRotate.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskRotate : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskRotate();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
