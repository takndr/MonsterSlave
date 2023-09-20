#include "Enemy/CBossController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"

#include "Enemy/CBoss.h"

#include "Global.h"

ACBossController::ACBossController()
{
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent(this, &Perception, "Perception");


}

void ACBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedBoss = Cast<ACBoss>(InPawn);

	UBehaviorTree* behaviorTree = PossessedBoss->GetBehaviorTree();
	CheckNull(behaviorTree);

	UseBlackboard(behaviorTree->GetBlackboardAsset(), Blackboard);
	RunBehaviorTree(behaviorTree);
}