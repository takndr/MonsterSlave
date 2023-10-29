#include "CEquipItem.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

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

	CHelpers::GetAsset(&DissolveCurve, "/Game/Items/Weapons/_Asset/Dissolve/Curve_Dissolve");
}

void ACEquipItem::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(Owner);
	WeaponComp = CHelpers::GetComponent<UCWeaponComponent>(Owner);

	DynamicMaterial = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), nullptr);
	StaticMesh->SetMaterial(0, DynamicMaterial);

	OnTimeline.BindUFunction(this, "Dissolving");
	Timeline.AddInterpFloat(DissolveCurve, OnTimeline);
	Timeline.SetPlayRate(2.0f);
}

void ACEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);
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

void ACEquipItem::FirstSkill()
{
	CheckNull(FirstSkillMontage);
	Owner->PlayAnimMontage(FirstSkillMontage);
}

void ACEquipItem::SecondSkill()
{
	CheckNull(SecondSkillMontage);
	Owner->PlayAnimMontage(SecondSkillMontage);
}

void ACEquipItem::Equip()
{
	if (EquipMontage == nullptr) {
		Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
		Owner->bUseControllerRotationYaw = true;
		Attach();
		Equipped();
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
		Detach();
		UnEquipped();
		return;
	}

	CheckNull(StateComp);
	StateComp->SetEquip();
	Owner->PlayAnimMontage(UnEquipMontage);
}

void ACEquipItem::Attach()
{
	Timeline.PlayFromStart();
	FLatentActionInfo actionInfo;
	UKismetSystemLibrary::Delay(GetWorld(), 0.5, actionInfo);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquippedHolster);
	Timeline.ReverseFromEnd();
}

void ACEquipItem::Detach()
{
	Timeline.PlayFromStart();
	FLatentActionInfo actionInfo;
	UKismetSystemLibrary::Delay(GetWorld(), 0.5, actionInfo);
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), UnEquippedHolster);
	Timeline.ReverseFromEnd();
}

void ACEquipItem::Equipped()
{
	CheckNull(StateComp);

	StateComp->SetIdle();
}

void ACEquipItem::UnEquipped()
{
	CheckNull(StateComp);
	CheckNull(WeaponComp);

	StateComp->SetIdle();
	WeaponComp->SetUnarmed();

	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	Owner->bUseControllerRotationYaw = false;
}

void ACEquipItem::Dissolving(float Output)
{
	DynamicMaterial->SetScalarParameterValue("Amount", Output);
}