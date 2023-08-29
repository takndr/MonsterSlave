#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Items/Weapons/CBowAnimInstance.h"
#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACEquipBow::ACEquipBow() {
	WeaponType = EWeaponType::Bow;

	ConstructorHelpers::FClassFinder<UCBowAnimInstance> animAsset(TEXT("AnimBlueprint'/Game/Items/Weapons/Bow/ABP_EquipBow.ABP_EquipBow_C'"));
	if (animAsset.Succeeded()) {
		SkeletalMesh->SetAnimInstanceClass(animAsset.Class);
	}
}

void ACEquipBow::Attack() {
	CheckNull(AttackMontage);
	CheckNull(AimAttackMontage);
	CheckNull(Owner);
	Super::Attack();

	CLog::Log("Bow Attack");

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage);
		SkeletalMesh->GetAnimInstance()->Montage_Play(AimAttackBowMontage);
	}
	else {
		player->PlayAnimMontage(AttackMontage);
		SkeletalMesh->GetAnimInstance()->Montage_Play(AttackBowMontage);
	}
}


void ACEquipBow::OnAim() {
	Super::OnAim();

	CLog::Log("Bow OnAim Called");
	if (OnAimBowMontage == nullptr) {
		CLog::Log("Set OnAimBowMontage");
		return;
	}
	SkeletalMesh->GetAnimInstance()->Montage_Play(OnAimBowMontage);
}


void ACEquipBow::OffAim() {
	Super::OffAim();

	CLog::Log("Bow OffAim Called");
	if (OffAimBowMontage == nullptr) {
		CLog::Log("Set OffAimBowMontage");
		return;
	}
	SkeletalMesh->GetAnimInstance()->Montage_Play(OffAimBowMontage);
}

void ACEquipBow::Equipped() {
	Super::Equipped();

	// 활에 화살 붙이기
	SpawnArrow();
}

void ACEquipBow::SpawnArrow() {
	Arrow = ACArrow::Spawn( GetWorld(), Owner);
	CheckNull(Arrow);
	Arrow->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "Bow_Arrow_Slot");
}