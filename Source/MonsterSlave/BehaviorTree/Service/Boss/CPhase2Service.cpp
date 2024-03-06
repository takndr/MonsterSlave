#include "BehaviorTree/Service/Boss/CPhase2Service.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"
#include "Player/CPlayer.h"

#include "Global.h"

void UCPhase2Service::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	//Controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
	//OwnerBoss = Controller->GetPossessedBoss();

	ACBossController* controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
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
	float doc = bossForward.GetSafeNormal2D() | temp.GetSafeNormal2D();

	if (boss->bCanBreath)
	{
		if (doc < 0.98)
		{
			behaviorComp->SetRotateMode();
			return;
		}

		behaviorComp->SetBreathMode();
		return;
	}

	behaviorComp->SetPatrolMode();
}

void UCPhase2Service::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	//CheckNull(controller);

	//UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	//CheckNull(behaviorComp);

	//ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	//CheckNull(boss);

	//ACPlayer* player = behaviorComp->GetPlayerKey();
	//CheckNull(player);

	//FVector bossForward = boss->GetActorForwardVector();
	//FVector bossLoc = boss->GetActorLocation();
	//FVector playerLoc = player->GetActorLocation();
	//FVector temp = playerLoc - bossLoc;
	//float doc = bossForward.GetSafeNormal2D() | temp.GetSafeNormal2D();

	//if (boss->bCanBreath)
	//{
	//	if (doc < 0.98)
	//	{
	//		behaviorComp->SetRotateMode();
	//		CLog::Log("Boss Set Rotate Mode");
	//		return;
	//	}

	//	behaviorComp->SetBreathMode();
	//	CLog::Log("Boss Set Breath Mode");
	//	return;
	//}

	//behaviorComp->SetPatrolMode();
	//CLog::Log("Boss Set Patrol Mode");
}