#include "BehaviorTree/Service/Boss/CPhase2Service.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"
#include "Player/CPlayer.h"

#include "Global.h"

void UCPhase2Service::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
	OwnerBoss = Controller->GetPossessedBoss();
}

void UCPhase2Service::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNull(boss);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	CheckNull(player);

	// boss�� ���溤�Ϳ� �÷��̾��� ���溤�Ͱ� -1�� �ƴҰ�쿡�� Rotate��� -> ������ �ƴѰͰ���
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

		behaviorComp->SetActionMode();
		return;
	}

	behaviorComp->SetPatrolMode();
}