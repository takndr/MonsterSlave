#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskMove.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskMove();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
