#include "Notifies/CAnimNotifyStateBowAttack.h"

#include "Global.h"

FString UCAnimNotifyStateBowAttack::GetNotifyName_Implementation() const {
	return "BowAttack";
}

void UCAnimNotifyStateBowAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// 화살 프로젝타일 켜기

	// 화살 콜리젼 켜기


}

void UCAnimNotifyStateBowAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	
	// 화살 리스폰 하기
}