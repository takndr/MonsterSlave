#include "BehaviorTree/Task/CTaskPhaseChange.h"

#include "Global.h"
// Boss�� PhaseChangeMontage �迭���� ���� Phase�� ������ �ִ� Montage�� �����Ѵ�
EBTNodeResult::Type UCTaskPhaseChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	CLog::Print("Phase Change!!");
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UCTaskPhaseChange::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	return EBTNodeResult::Succeeded;
}

void UCTaskPhaseChange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	return;
}

void UCTaskPhaseChange::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) {

	return;
}