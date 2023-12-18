#include "Enemy/CDummyEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Widgets/Enemy/CDummyHp.h"
#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"
#include "Quest/CQuestData.h"

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

	// TODO : HP Widget을 플레이어쪽으로 향하게 / 이거를 Tick에서 매번 확인해야하나?
	// 즉, HP Widget과 플레이어
}

void ACDummyEnemy::OnCollision()
{
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACDummyEnemy::OffCollision()
{
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ClearHittedCharacters();

	bHitNormal = false;
	bHitKnockback = false;
}

void ACDummyEnemy::Attack()
{
	CheckFalse(StateComponent->IsIdle());
	if (bCanSkill)
	{
		CheckNull(SkillMontage);
		StateComponent->SetAction();
		bHitKnockback = true;
		PlayAnimMontage(SkillMontage);
		bCanSkill = false;
		UKismetSystemLibrary::K2_SetTimer(this, "OnSkillCoolDown", SkillCoolDown, false);
	}
	else
	{
		CheckNull(AttackMontage);
		StateComponent->SetAction();
		bHitNormal = true;
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

	FDamageEvent damageEvent;
	OtherActor->TakeDamage(AttackDamage, damageEvent, GetController(), this);
}

float ACDummyEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	StatusComponent->DecreaseHealth(DamageValue);

	//LaunchCharacter(FVector(0, 0, 100), false, false);
	//GetCharacterMovement()->Launch(FVector(0, 0, Damage));

	UCDummyHp* hpWidget = Cast<UCDummyHp>(HPWidget->GetUserWidgetObject());
	hpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	if (StatusComponent->IsDead())
	{
		StateComponent->SetDead();
		Dead();
		return DamageValue;
	}

	Hitted(DamageCauser);

	return DamageValue;
}

void ACDummyEnemy::Hitted(AActor* DamageCauser)
{
	CheckNull(HitMontage);
	CheckNull(KnockbackMontage);

	ACEquipItem* item = Cast<ACEquipItem>(DamageCauser);
	CheckNull(item);

	if (item->IsNormalHit())
	{
		PlayAnimMontage(HitMontage);
	}

	if (item->IsKnockBackHit())
	{
		PlayAnimMontage(KnockbackMontage);
	}
}

void ACDummyEnemy::Dead()
{
	CheckNull(DieMontage);
	PlayAnimMontage(DieMontage);

	StateComponent->SetDead();

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	Weapon->SetGenerateOverlapEvents(false);
	HPWidget->SetVisibility(false);

	UKismetSystemLibrary::K2_SetTimer(this, "EndDead", 3.0f, false);
}

void ACDummyEnemy::EndDead()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (auto quest : player->Quests)
	{
		if (quest->OnQuestCheck.IsBound())
		{
			quest->OnQuestCheck.Execute(this);
		}
	}

	this->Destroy();
}