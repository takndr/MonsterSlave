#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CRootService.generated.h"

UCLASS()
class MONSTERSLAVE_API UCRootService : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

// ==================================================================
public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector PhaseKey;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector PhaseChangedKey;

private:
	class ACBossController* Controller;
	class ACBoss* OwnerBoss;
};
