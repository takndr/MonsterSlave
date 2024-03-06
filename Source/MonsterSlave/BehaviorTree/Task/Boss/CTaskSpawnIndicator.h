#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CTaskSpawnIndicator.generated.h"

UCLASS()
class MONSTERSLAVE_API UCTaskSpawnIndicator : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCTaskSpawnIndicator();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float RunningTime;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> IndicatorClass;

	UPROPERTY(EditAnywhere)
		float Delay = 2.0f;
};
