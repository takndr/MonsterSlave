#include "BehaviorTree/Task/Boss/CTaskSpawnIndicator.h"

#include "Component/CStateComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"

//#include "GameFramework/Actor.h"

#include "Global.h"

UCTaskSpawnIndicator::UCTaskSpawnIndicator()
{
	NodeName = "Spawn Indicator";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskSpawnIndicator::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	RunningTime = 0.0f;

	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNullResult(controller, EBTNodeResult::Failed);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNullResult(boss, EBTNodeResult::Failed);

	CheckNullResult(IndicatorClass, EBTNodeResult::Failed);

	controller->StopMovement();
	// Indicator ½ºÆù
	GetWorld()->SpawnActor<AActor>(IndicatorClass, FVector(0, 0, -88), FRotator(0, -90, 0))->AttachToActor(boss, FAttachmentTransformRules::KeepRelativeTransform);

	return EBTNodeResult::InProgress;
}

void UCTaskSpawnIndicator::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	RunningTime += DeltaSeconds;

	if (RunningTime >= Delay)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}