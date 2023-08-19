#include "CEquipItem.h"

#include "GameFramework/Character.h"

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
}

void ACEquipItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACEquipItem::Equip() {
	if (EquipMontage == nullptr) {
		CLog::Log("Set Equip Montage");
		return;
	}

	CheckTrue(bEquip);
	bEquip = true;

	//Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	//Owner->bUseControllerRotationYaw = false;
	ACPlayer* player = Cast<ACPlayer>(Owner);
	player->SetCurrentWeapon(this);

	Owner->PlayAnimMontage(EquipMontage);
}

void ACEquipItem::UnEquip() {
	if (UnEquipMontage == nullptr) {
		CLog::Log("Set UnEquip Montage");
		return;
	}

	CheckTrue(bEquip);
	bEquip = true;

	//Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
	//Owner->bUseControllerRotationYaw = true;
	

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
	bEquip = false;
	ACPlayer* player = Cast<ACPlayer>(Owner);
	player->SetWeaponType(WeaponType);
}

void ACEquipItem::UnEquipped() {
	CLog::Log("EquipItem UnEquipped Called");
	bEquip = false;
	ACPlayer* player = Cast<ACPlayer>(Owner);
	player->SetWeaponType(EWeaponType::None);
	player->SetCurrentWeapon(nullptr);
}