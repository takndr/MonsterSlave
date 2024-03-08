#include "BehaviorTree/Task/Dummy/CTaskDummyAttack.h"

#include "Component/CStateComponent.h"
#include "Component/CBehaviorComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Enemy/CDummyController.h"
#include "Player/CPlayer.h"

#include "Global.h"

UCTaskDummyAttack::UCTaskDummyAttack()
{
	NodeName = "Attack";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskDummyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	RunningTime = 0.0f;

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNullResult(behaviorComp, EBTNodeResult::Failed);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	CheckNullResult(player, EBTNodeResult::Failed);

	// 공격하기 전에 플레이어 쪽으로 돌아보고 공격
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(enemy->GetActorLocation(), player->GetActorLocation());
	enemy->SetActorRotation(FQuat(rotation));
	enemy->Attack();

	return EBTNodeResult::InProgress;
}

void UCTaskDummyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACDummyController* controller = Cast<ACDummyController>(OwnerComp.GetOwner());
	CheckNull(controller);

	ACDummyEnemy* enemy = Cast<ACDummyEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(enemy);
	CheckNull(stateComp);

	RunningTime += DeltaSeconds;

	if (stateComp->IsIdle() && (RunningTime >= Delay))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}