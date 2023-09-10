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

	// ȭ�� ������Ÿ�� �ѱ�
	// ȭ�� �ݸ��� �ѱ�
	CLog::Log("Bow Shoot Arrow");
	bow->ShotArrow();

}

void UCAnimNotifyStateBowAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);
	// ȭ�� ������ �ϱ�
	ACEquipBow* bow = Cast<ACEquipBow>(MeshComp->GetOwner());
	CheckNull(bow);

	bow->SpawnArrow();
}