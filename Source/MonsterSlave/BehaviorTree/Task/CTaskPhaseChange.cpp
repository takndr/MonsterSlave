#include "BehaviorTree/Task/CTaskPhaseChange.h"

#include "Global.h"
// Boss의 PhaseChangeMontage 배열에서 현재 Phase의 순서에 있는 Montage를 실행한다
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