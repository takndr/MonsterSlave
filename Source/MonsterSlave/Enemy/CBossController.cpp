#include "Enemy/CBossController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Enemy/CBoss.h"

#include "Global.h"

ACBossController::ACBossController()
{
	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	Blackboard;
}

void ACBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ACBoss* boss = Cast<ACBoss>(InPawn);
	CheckNull(boss);

	PossessedBoss = boss;

	UBehaviorTree* behaviorTree = boss->GetBehaviorTree();
	CheckNull(behaviorTree);

	Blackboard->InitializeBlackboard(*(behaviorTree->GetBlackboardAsset()));

	
	RunBehaviorTree(behaviorTree);
}