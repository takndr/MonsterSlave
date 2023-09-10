#include "Notifies/CAnimNotifyStateBowAttack.h"

#include "Items/Weapons/CEquipBow.h"
#include "Items/Weapons/CArrow.h"

#include "Global.h"

FString UCAnimNotifyStateBowAttack::GetNotifyName_Implementation() const {
	return "BowAttack";
}

void UCAnimNotifyStateBowAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACEquipBow* bow = Cast<ACEquipBow>(MeshComp->GetOwner());
	CheckNull(bow);

	ACArrow* arrow = bow->GetArrow();
	CheckNull(arrow);

	// 화살 프로젝타일 켜기
	// 화살 콜리젼 켜기
	CLog::Log("Bow Shoot Arrow");
	bow->ShotArrow();

}

void UCAnimNotifyStateBowAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	// 화살 리스폰 하기
	ACEquipBow* bow = Cast<ACEquipBow>(MeshComp->GetOwner());
	CheckNull(bow);

	bow->SpawnArrow();
}