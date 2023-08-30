#include "Notifies/CAnimNotifyStateCollision.h"

#include "Global.h"

FString UCAnimNotifyStateCollision::GetNotifyName_Implementation() const {
	return "Collision";
}

void UCAnimNotifyStateCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// ���� �ݸ��� �ѱ�
}

void UCAnimNotifyStateCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);

	// ���� �ݸ��� ����
}