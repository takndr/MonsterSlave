#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskDummyAttack.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskDummyAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskDummyAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ==================================================================
private:
	float RunningTime = 0.0f;
// ==================================================================
private:
	UPROPERTY(EditAnywhere)
		float Delay = 2.0f;
};
