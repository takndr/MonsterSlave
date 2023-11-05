#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CDummyService.generated.h"

UCLASS()
class MONSTERSLAVE_API UCDummyService : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ==================================================================
private:
	class ACDummyController* Controller;
	class ACDummyEnemy* OwnerDummy;
};
