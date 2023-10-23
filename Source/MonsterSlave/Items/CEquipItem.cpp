#include "CEquipItem.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

ACEquipItem::ACEquipItem()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &StaticMesh, "Mesh", Scene);

	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACEquipItem::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(Owner);
	WeaponComp = CHelpers::GetComponent<UCWeaponComponent>(Owner);
}

void ACEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEquipItem::Attack() 
{
	CheckTrue(AttackMontage.Num() == 0);
	CheckNull(Owner);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;
		return;
	}
	CheckFalse(StateComp->IsIdle());
	StateComp->SetAction();

	Owner->PlayAnimMontage(AttackMontage[ComboCount]);
}

void ACEquipItem::NextCombo()
{
	CheckFalse(bSucceed);
	CheckNull(Owner);

	bSucceed = false;
	ComboCount++;

	Owner->PlayAnimMontage(AttackMontage[ComboCount]);
}

void ACEquipItem::EndAttack()
{
	StateComp->SetIdle();
	ComboCount = 0;
}

void ACEquipItem::Equip()
{
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

void ACEquipItem::UnEquip()
{
	if (UnEquipMontage == nullptr) {
		CLog::Log("Set UnEquip Montage");
		return;
	}
	CheckNull(StateComp);
	StateComp->SetEquip();

	Owner->PlayAnimMontage(UnEquipMontage);
}

void ACEquipItem::Attach()
{
	CLog::Log("EquipItem Attach Called");
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquippedHolster);
}

void ACEquipItem::Detach()
{
	CLog::Log("EquipItem Detach Called");
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), UnEquippedHolster);
}

void ACEquipItem::Equipped()
{
	CLog::Log("EquipItem Equipped Called");
	CheckNull(StateComp);

	StateComp->SetIdle();
}

void ACEquipItem::UnEquipped()
{
	CLog::Log("EquipItem UnEquipped Called");
	CheckNull(StateComp);
	CheckNull(WeaponComp);

	StateComp->SetIdle();
	WeaponComp->SetUnarmed();

	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	Owner->bUseControllerRotationYaw = false;
}
