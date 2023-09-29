#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskBiteAttack.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskBiteAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskBiteAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ==================================================================
private:
	float RunningTime;
// ==================================================================
private:
	UPROPERTY(EditAnywhere)
		float Delay = 2.0f;
};
