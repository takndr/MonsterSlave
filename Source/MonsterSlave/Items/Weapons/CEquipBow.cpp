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

void ACEquipBow::BeginPlay() {
	Super::BeginPlay();

	UAnimInstance* anim = SkeletalMesh->GetAnimInstance();
	CheckNull(anim);
	UCBowAnimInstance* bowAnim = Cast<UCBowAnimInstance>(anim);
	CheckNull(bowAnim);
	bowAnim->SetOwnerCharacter(Owner);
}

void ACEquipBow::Attack() {
	// attack몽타주의 길이가 0보다 클때 진행하도록 조건 설정
	Super::Attack();

	CLog::Log("Bow Attack");

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage[ComboCount]);
		SkeletalMesh->GetAnimInstance()->Montage_Play(AimAttackBowMontage);
	}
	else {
		player->PlayAnimMontage(AttackMontage[ComboCount]);
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
	Arrow->AttachToComponent(SkeletalMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "arrow_socket");
}