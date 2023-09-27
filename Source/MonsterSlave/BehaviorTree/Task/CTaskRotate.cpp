#include "BehaviorTree/Task/CTaskRotate.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"
#include "Player/CPlayer.h"

#include "Global.h"

UCTaskRotate::UCTaskRotate()
{
	NodeName = "Rotate";
	bNotifyTick = true;
}

EBTNodeResult::Type UCTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UCTaskRotate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	CLog::Log("Rotate Task Start");
	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNull(boss);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	CheckNull(player);

	FVector bossForward = boss->GetActorForwardVector();
	FVector bossLoc = boss->GetActorLocation();
	FVector playerLoc = player->GetActorLocation();
	FVector temp = playerLoc - bossLoc;

	FRotator rotation = UKismetMathLibrary::RInterpTo(boss->GetActorRotation(), temp.Rotation(), DeltaSeconds, 2.0f);
	boss->SetActorRotation(rotation);

	float doc = bossForward.GetSafeNormal2D() | temp.GetSafeNormal2D();

	if (doc > 0.85)
	{
		CLog::Print("RotateTask End");
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
