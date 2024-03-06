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
	
	// �÷��̾ ���� ���� ���� ��� Patrol Mode
	if (player == nullptr)
	{
		behaviorComp->SetPatrolMode();
		return;
	}
	
	// ������ �Ǿ� �ִ� �����̸� Move Mode
	float distance = player->GetDistanceTo(OwnerDummy);
	if (distance >= 300)
	{
		behaviorComp->SetMoveMode();
		return;
	}

	// ������� �Ÿ��� ����� ������ ActionMode
	behaviorComp->SetActionMode();
}

// � ��带 ���ϱ� ���� ���� �ð��� ��� �ð��� �־�� �� �� ����