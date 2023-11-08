#include "Enemy/CDummyEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Widgets/Enemy/CDummyHp.h"
#include "Player/CPlayer.h"

#include "Global.h"

ACDummyEnemy::ACDummyEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Weapon, "Weapon", GetMesh());
	CHelpers::CreateSceneComponent(this, &HPWidget, "HPWidget", GetCapsuleComponent());

	CHelpers::CreateActorComponent(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent(this, &StateComponent, "State");
	
	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");

	// HP Widget Setting
	CHelpers::GetClass(&HPWidgetClass, "/Game/Widgets/Widget/Enemy/WB_DummyHp");
	HPWidget->SetRelativeLocation(FVector(0, 0, 90));
	HPWidget->SetDrawSize(FVector2D(100, 10));
	HPWidget->SetWidgetClass(HPWidgetClass);
	
	// AI Controller Setting
	CHelpers::GetClass(&AIControllerClass, "/Game/DummyEnemy/BP_CDummyController");
}

void ACDummyEnemy::BeginPlay()
{
	Super::BeginPlay();

	HPWidget->InitWidget();
	UCDummyHp* hpWidget = Cast<UCDummyHp>(HPWidget->GetUserWidgetObject());
	CheckNull(hpWidget);
	hpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	Weapon->OnComponentBeginOverlap.AddDynamic(this, &ACDummyEnemy::OnOverlap);
	
}


void ACDummyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDummyEnemy::OnCollision()
{
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACDummyEnemy::OffCollision()
{
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ClearHittedCharacters();
}

void ACDummyEnemy::Attack()
{
	CheckFalse(StateComponent->IsIdle());
	if (bCanSkill)
	{
		CheckNull(SkillMontage);
		StateComponent->SetAction();
		PlayAnimMontage(SkillMontage);
		bCanSkill = false;
		UKismetSystemLibrary::K2_SetTimer(this, "OnSkillCoolDown", SkillCoolDown, false);
	}
	else
	{
		CheckNull(AttackMontage);
		StateComponent->SetAction();
		PlayAnimMontage(AttackMontage);
	}
}

void ACDummyEnemy::EndAttack()
{
	StateComponent->SetIdle();
}

void ACDummyEnemy::OnSkillCoolDown()
{
	bCanSkill = true;
}

void ACDummyEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == this);

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	if (HittedCharacters.Find(player) != -1) {
		return;
	}
	HittedCharacters.AddUnique(player);

	// TODO : 스킬인지, 일반 공격인지
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(30.0f, damageEvent, GetController(), this);
}

float ACDummyEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StatusComponent->DecreaseHealth(DamageValue);

	UCDummyHp* hpWidget = Cast<UCDummyHp>(HPWidget->GetUserWidgetObject());
	hpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	if (StatusComponent->IsDead())
	{
		StateComponent->SetDead();
		Dead();
		return DamageValue;
	}

	Hitted(DamageEvent);

	return DamageValue;
}

void ACDummyEnemy::Hitted(FDamageEvent const& DamageEvent)
{
	CheckNull(HitMontage);
	CheckNull(KnockbackMontage);

	if (DamageEvent.ClassID == 0)
	{
		PlayAnimMontage(HitMontage);
	}
	else
	{
		PlayAnimMontage(KnockbackMontage);
	}
}

void ACDummyEnemy::Dead()
{
	CheckNull(DieMontage);
	StateComponent->SetDead();
	PlayAnimMontage(DieMontage);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	Weapon->SetGenerateOverlapEvents(false);
	UKismetSystemLibrary::K2_SetTimer(this, "EndDead", 3.0f, false);
}

void ACDummyEnemy::EndDead()
{
	this->Destroy();
}