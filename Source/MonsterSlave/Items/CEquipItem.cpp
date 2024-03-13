#include "CEquipItem.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Component/CStateComponent.h"
#include "Component/CPlayerStatusComponent.h"
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

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	WeaponComp = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);

	DynamicMaterial = UMaterialInstanceDynamic::Create(StaticMesh->GetMaterial(0), nullptr);
	StaticMesh->SetMaterial(0, DynamicMaterial);

	OnTimeline.BindUFunction(this, "Dissolving");
	Timeline.AddInterpFloat(DissolveCurve, OnTimeline);
	Timeline.SetPlayRate(2.0f);

	FirstSkillTemp = FirstSkillCoolDown;
	SecondSkillTemp = SecondSkillCoolDown;
}

void ACEquipItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timeline.TickTimeline(DeltaTime);

	if (bCanFirstSkill == false)
	{
		FirstSkillTemp -= DeltaTime;
		FirstSkillTemp = FMath::Clamp(FirstSkillTemp, 0.0f, FirstSkillCoolDown);

		if (OnFirstSkillCoolDown.IsBound())
		{
			OnFirstSkillCoolDown.Broadcast(FirstSkillTemp);
		}
	}

	if (bCanSecondSkill == false)
	{
		SecondSkillTemp -= DeltaTime;
		SecondSkillTemp = FMath::Clamp(SecondSkillTemp, 0.0f, SecondSkillCoolDown);

		if (OnSecondSkillCoolDown.IsBound())
		{
			OnSecondSkillCoolDown.Broadcast(SecondSkillTemp);
		}
	}
}

void ACEquipItem::Attack() 
{
	CheckTrue(AttackMontage.Num() == 0);
	CheckNull(OwnerCharacter);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;
		return;
	}
	CheckFalse(StateComp->IsIdle());

	UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
	CheckNull(statusComp);

	StateComp->SetAction();
	OwnerCharacter->PlayAnimMontage(AttackMontage[ComboCount], 1.0f + statusComp->GetSpeedStat() * 0.25f);
}

void ACEquipItem::NextCombo()
{
	CheckFalse(bSucceed);
	CheckNull(OwnerCharacter);

	UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
	CheckNull(statusComp);

	bSucceed = false;
	ComboCount++;

	OwnerCharacter->PlayAnimMontage(AttackMontage[ComboCount], 1.0f + statusComp->GetSpeedStat() * 0.25f);
}

void ACEquipItem::EndAttack()
{
	StateComp->SetIdle();
	ComboCount = 0;
	bNormal = false;
	bKnockBack = false;

	OffCollision();
}

void ACEquipItem::FirstSkill()
{
	CheckNull(FirstSkillMontage);
	CheckFalse(bCanFirstSkill);

	UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
	CheckNull(statusComp);

	StateComp->SetAction();
	OwnerCharacter->PlayAnimMontage(FirstSkillMontage, 1.0f + statusComp->GetSpeedStat() * 0.25f);

	bCanFirstSkill = false;
	UKismetSystemLibrary::K2_SetTimer(this, "EndFirstSkillCool", FirstSkillCoolDown, false);
}

void ACEquipItem::EndFirstSkillCool()
{
	bCanFirstSkill = true;
	FirstSkillTemp = FirstSkillCoolDown;

	if (OffFirstSkillCoolDown.IsBound())
	{
		OffFirstSkillCoolDown.Broadcast();
	}
}

void ACEquipItem::SecondSkill()
{
	CheckNull(SecondSkillMontage);
	CheckFalse(bCanSecondSkill);

	UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
	CheckNull(statusComp);

	StateComp->SetAction();
	OwnerCharacter->PlayAnimMontage(SecondSkillMontage, 1.0f + statusComp->GetSpeedStat() * 0.25f);

	bCanSecondSkill = false;
	UKismetSystemLibrary::K2_SetTimer(this, "EndSecondSkillCool", SecondSkillCoolDown, false);
}

void ACEquipItem::EndSecondSkillCool()
{
	bCanSecondSkill = true;
	SecondSkillTemp = SecondSkillCoolDown;

	if (OffSecondSkillCoolDown.IsBound())
	{
		OffSecondSkillCoolDown.Broadcast();
	}
}

void ACEquipItem::Equip()
{
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	OwnerCharacter->bUseControllerRotationYaw = true;

	Attach();
}

void ACEquipItem::UnEquip()
{
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	OwnerCharacter->bUseControllerRotationYaw = false;

	ComboCount = 0;
	Detach();
}

void ACEquipItem::Attach()
{
	Timeline.PlayFromStart();
	FLatentActionInfo actionInfo;
	UKismetSystemLibrary::Delay(GetWorld(), 0.5, actionInfo);
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), EquippedHolster);
	Timeline.ReverseFromEnd();
}

void ACEquipItem::Detach()
{
	Timeline.PlayFromStart();
	FLatentActionInfo actionInfo;
	UKismetSystemLibrary::Delay(GetWorld(), 0.5, actionInfo);
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), UnEquippedHolster);
	Timeline.ReverseFromEnd();
}

void ACEquipItem::Dissolving(float Output)
{
	DynamicMaterial->SetScalarParameterValue("Amount", Output);
}

void ACEquipItem::SetHitNormal()
{
	bNormal = true;
}

void ACEquipItem::SetHitKnockBack()
{
	bKnockBack = true;
}
