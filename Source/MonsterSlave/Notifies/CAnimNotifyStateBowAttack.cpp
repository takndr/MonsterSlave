#include "Notifies/CAnimNotifyStateBowAttack.h"

#include "Global.h"

FString UCAnimNotifyStateBowAttack::GetNotifyName_Implementation() const {
	return "BowAttack";
}

void UCAnimNotifyStateBowAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// ȭ�� ������Ÿ�� �ѱ�

	// ȭ�� �ݸ��� �ѱ�


}

void UCAnimNotifyStateBowAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	
	// ȭ�� ������ �ϱ�
}