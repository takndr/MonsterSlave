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
	// TODO : 보스의 공격 선택(보강)
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

	// boss의 전방벡터와 플레이어의 전방벡터가 -1이 아닐경우에는 Rotate모드 -> 내적은 아닌것같음
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
	

	// boss의 거리가 플레이어와의 일정 거리가 아니면 Move모드 -> 어떤 공격이냐에 따라 거리가 달라지는데?
	float distance = player->GetDistanceTo(boss);
	if (distance >= 1000)
	{
		behaviorComp->SetMoveMode();
		return;
	}

	behaviorComp->SetActionMode();
	// boss의 거리가 플레이어와의 일정 거리가 충족하면 Action모드


}