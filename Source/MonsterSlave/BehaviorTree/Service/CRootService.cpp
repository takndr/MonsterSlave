#include "BehaviorTree/Service/CRootService.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

#include "Global.h"

/*
	Blackboard->SetValueAsBool();
	Blackboard->SetValueAsClass();
	Blackboard->SetValueAsEnum();
	Blackboard->SetValueAsFloat();
	Blackboard->SetValueAsInt();
	Blackboard->SetValueAsName();
	Blackboard->SetValueAsObject();
	Blackboard->SetValueAsRotator();
	Blackboard->SetValueAsString();
	Blackboard->SetValueAsVector();
*/

void UCRootService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
	OwnerBoss = Controller->GetPossessedBoss();
	
	Controller->GetBlackboardComponent()->SetValueAsBool("PhaseChangedKey", OwnerBoss->IsAblePhaseChange());
	Controller->GetBlackboardComponent()->SetValueAsInt("PhaseKey", OwnerBoss->GetCurrentPhase());
}

void UCRootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}