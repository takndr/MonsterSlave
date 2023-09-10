#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Items/Weapons/CBowAnimInstance.h"
#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACEquipBow::ACEquipBow() {
	WeaponType = EWeaponType::Bow;

	ConstructorHelpers::FClassFinder<UCBowAnimInstance> animAsset(TEXT("AnimBlueprint'/Game/Items/Weapons/Bow/ABP_EquipBow.ABP_EquipBow_C'"));
	if (animAsset.Succeeded()) {
		SkeletalMesh->SetAnimInstanceClass(animAsset.Class);
	}

	CHelpers::GetClass(&ArrowClass, "/Game/Items/Weapons/Arrow/BP_Arrow");
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
	// attack��Ÿ���� ���̰� 0���� Ŭ�� �����ϵ��� ���� ����
	Super::Attack();

	CheckFalse(StateComp->IsIdle());
	CheckTrue(AimAttackMontage.Num() == 0);
	CheckTrue(AttackMontage.Num() == 0);

	StateComp->SetAttack();

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

void ACEquipBow::EndAttack() {
	Super::EndAttack();

	StateComp->SetIdle();
	ComboCount = 0;

	// TODO : ȭ�� ���ȯ

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

	// Ȱ�� ȭ�� ���̱�
	SpawnArrow();
}

void ACEquipBow::UnEquipped() {
	Super::UnEquipped();

	// Ȱ�� ȭ�� ���̱�
	if (Arrow != nullptr) {
		Arrow->Destroy();
		Arrow = nullptr;
	}
}

void ACEquipBow::ShotArrow() {
	CheckNull(Arrow);

	Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Arrow->ShootArrow();
}

void ACEquipBow::SpawnArrow() {
	FTransform transform = SkeletalMesh->GetSocketTransform("arrow_socket");
	Arrow = GetWorld()->SpawnActorDeferred<ACArrow>(ArrowClass, transform, Owner);
	Arrow->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, "arrow_socket");
	Arrow->FinishSpawning(transform);
}