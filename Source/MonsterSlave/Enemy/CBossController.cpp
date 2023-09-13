#include "Enemy/CBossController.h"

#include "Enemy/CBoss.h"

#include "Global.h"

void ACBossController::OnPossess(APawn* InPawn) {
	ACBoss* boss = Cast<ACBoss>(InPawn);
	CheckNull(boss);

	PossessedBoss = boss;

	UBehaviorTree* behaviorTree = boss->GetBehaviorTree();
	CheckNull(behaviorTree);

	RunBehaviorTree(behaviorTree);
}