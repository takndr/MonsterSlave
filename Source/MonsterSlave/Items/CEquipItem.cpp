#include "CEquipItem.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Player/CPlayer.h"

#include "Global.h"

ACEquipItem::ACEquipItem() {
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "Mesh", Scene);
}

void ACEquipItem::BeginPlay() {
	Super::BeginPlay();
	CLog::Log("EquipItem BeginPlay Called");
	Owner = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(Owner);
	WeaponComp = CHelpers::GetComponent<UCWeaponComponent>(Owner);
}

void ACEquipItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACEquipItem::Attack() {
	CheckNull(StateComp);

	StateComp->SetAttack();
}


void ACEquipItem::Equip() {
	if (EquipMontage == nullptr) {
		CLog::Log("Set Equip Montage");
		return;
	}
	CheckNull(StateComp);
	StateComp->SetEquip();

	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
	Owner->bUseControllerRotationYaw = true;
	Owner->PlayAnimMontage(EquipMontage);
}

void ACEquipItem::UnEquip() {
	if (UnEquipMontage == nullptr) {
		CLog::Log("Set UnEquip Montage");
		return;
	}
	CheckNull(StateComp);
	StateComp->SetEquip();

	Owner->PlayAnimMontage(UnEquipMontage);
}

void ACEquipItem::Attach() {
	CLog::Log("EquipItem Attach Called");
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquippedHolster);
}

void ACEquipItem::Detach() {
	CLog::Log("EquipItem Detach Called");
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), UnEquippedHolster);
}

void ACEquipItem::Equipped() {
	CLog::Log("EquipItem Equipped Called");
	CheckNull(StateComp);

	StateComp->SetIdle();
}

void ACEquipItem::UnEquipped() {
	// StateComponent
	CLog::Log("EquipItem UnEquipped Called");
	CheckNull(StateComp);
	CheckNull(WeaponComp);

	StateComp->SetIdle();
	WeaponComp->SetUnarmed();

	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	Owner->bUseControllerRotationYaw = false;
}

void ACEquipItem::OnAim() {
	CLog::Log("EquipItem OnAim Called");
	if (OnAimMontage == nullptr) {
		CLog::Log("Set OnAim Montage");
		return;
	}
	CheckNull(Owner);
	Owner->PlayAnimMontage(OnAimMontage);
}


void ACEquipItem::OffAim() {
	CLog::Log("EquipItem OffAim Called");
	if (OffAimMontage == nullptr) {
		CLog::Log("Set OffAim Montage");
		return;
	}
	CheckNull(Owner);
	Owner->PlayAnimMontage(OffAimMontage);
}