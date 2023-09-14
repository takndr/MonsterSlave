#include "BehaviorTree/Service/CRootService.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

#include "Global.h"

void UCRootService::OnSearchStart(FBehaviorTreeSearchData& SearchData) {
	ACBossController* controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
	OwnerBoss = controller->GetPossessedBoss();
	CLog::Print("Service Start : " + OwnerBoss->GetName());
	
	FBlackboardKeySelector;
	return;
}

void UCRootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	
}