#include "CRootService.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CBoss.h"
#include "Enemy/CBossController.h"
#include "Player/CPlayer.h"

#include "Global.h"

void UCRootService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Controller = Cast<ACBossController>(SearchData.OwnerComp.GetOwner());
	OwnerBoss = Controller->GetPossessedBoss();
	
	Controller->GetBlackboardComponent()->SetValueAsBool("PhaseChangedKey", OwnerBoss->IsAblePhaseChange());
	Controller->GetBlackboardComponent()->SetValueAsInt("PhaseKey", OwnerBoss->GetCurrentPhase());
}

void UCRootService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// TODO : ������ ���� ����(����)
	ACBossController* controller = Cast<ACBossController>(OwnerComp.GetOwner());
	CheckNull(controller);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	ACBoss* boss = Cast<ACBoss>(controller->GetPawn());
	CheckNull(boss);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(boss);
	CheckNull(stateComp);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	CheckNull(player);

	// boss�� ���溤�Ϳ� �÷��̾��� ���溤�Ͱ� -1�� �ƴҰ�쿡�� Rotate��� -> ������ �ƴѰͰ���
	FVector bossForward = boss->GetActorForwardVector();
	FVector bossLoc = boss->GetActorLocation();
	FVector playerLoc = player->GetActorLocation();
	FVector temp = playerLoc - bossLoc;
	float doc = bossForward.GetSafeNormal2D() | temp.GetSafeNormal2D();

	if (doc < 0.98)
	{
		behaviorComp->SetRotateMode();
		return;
	}
	

	// boss�� �Ÿ��� �÷��̾���� ���� �Ÿ��� �ƴϸ� Move��� -> � �����̳Ŀ� ���� �Ÿ��� �޶����µ�?
	float distance = player->GetDistanceTo(boss);
	if (distance >= 1000)
	{
		behaviorComp->SetMoveMode();
		return;
	}

	behaviorComp->SetActionMode();
	// boss�� �Ÿ��� �÷��̾���� ���� �Ÿ��� �����ϸ� Action���


}