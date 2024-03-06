#include "BehaviorTree/Service/Dummy/CDummyService.h"

#include "Component/CBehaviorComponent.h"
#include "Component/CStateComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Enemy/CDummyController.h"
#include "Player/CPlayer.h"

#include "Global.h"

void UCDummyService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	Controller = Cast<ACDummyController>(SearchData.OwnerComp.GetOwner());
	OwnerDummy = Cast<ACDummyEnemy>(Controller->GetPawn());
}

void UCDummyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(Controller);
	CheckNull(OwnerDummy);

	UCBehaviorComponent* behaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(Controller);
	CheckNull(behaviorComp);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(OwnerDummy);
	CheckNull(stateComp);

	ACPlayer* player = behaviorComp->GetPlayerKey();
	
	// 플레이어가 감지 되지 않을 경우 Patrol Mode
	if (player == nullptr)
	{
		behaviorComp->SetPatrolMode();
		return;
	}
	
	// 감지가 되어 있는 상태이면 Move Mode
	float distance = player->GetDistanceTo(OwnerDummy);
	if (distance >= 300)
	{
		behaviorComp->SetMoveMode();
		return;
	}

	// 어느정도 거리가 가까워 졌으면 ActionMode
	behaviorComp->SetActionMode();
}

// 어떤 모드를 취하기 전에 일정 시간의 대기 시간이 있어야 할 것 같음