#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CRootService.generated.h"

UCLASS()
class MONSTERSLAVE_API UCRootService : public UBTService
{
	GENERATED_BODY()
protected:
	/** called when search enters underlying branch
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

	/** update next tick interval
	 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

// ==================================================================
private:
	class ACBoss* OwnerBoss;
};
