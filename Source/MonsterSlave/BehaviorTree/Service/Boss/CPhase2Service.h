#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CPhase2Service.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPhase2Service : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
// ============================================================================
public:

private:
	class ACBossController* Controller;
	class ACBoss* OwnerBoss;
};
