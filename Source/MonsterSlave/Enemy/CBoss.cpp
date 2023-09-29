#include "Enemy/CBoss.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Widgets/CBossHp.h"
#include "Enemy/CBossController.h"
#include "etc/CDamageText.h"

#include "Global.h"

ACBoss::ACBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent(this, &StateComponent, "State");

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);
	
	// SkeletalMesh Setting
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/Boss/_Asset/Meshes/DragonTheUsurperSK");
	GetMesh()->SetSkeletalMesh(meshAsset);

	// Anim Class Setting
	TSubclassOf<UAnimInstance> animClass;
	CHelpers::GetClass(&animClass, "/Game/Boss/ABP_Boss");
	GetMesh()->SetAnimInstanceClass(animClass);

	// Collision Setting
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	// Widget Setting
	CHelpers::GetClass(&BossHpWidgetClass, "WidgetBlueprint'/Game/Widgets/Widget/Enemy/WB_BossHp.WB_BossHp_C'");

	// AI Controller Setting
	CHelpers::GetClass(&AIControllerClass, "/Game/Boss/BP_CBossController");

}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();
	BossHpWidget = CreateWidget<UCBossHp>(GetWorld(), BossHpWidgetClass);
	BossHpWidget->AddToViewport();

	CheckNull(BossHpWidget);
	BossHpWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());
	BossHpWidget->UpdateBossName(BossName);
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CheckTrueResult(bPhaseChange, Damage);

	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	StatusComponent->DecreaseHealth(DamageValue);

	// TODO : �������� ü�� ���� �����
	BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	// ������ �����ֱ�
	// TODO : damageTransform ����
	FTransform damageTransform = GetActorTransform();
	ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(ACDamageText::StaticClass(), damageTransform);
	damageText->FinishSpawning(damageTransform);
	damageText->SetDamageText(Damage);

	// ü�� ���� ������ ������ ��ȯ / ������ �������� ���� ���
	if (StatusComponent->IsDead())
	{
		// TODO : ���� ������ ������������ �ϵ��ڵ����� �־� ������
		if (BossPhase == 2)
		{
			PlayAnimMontage(DieMontage);
			GetMesh()->SetGenerateOverlapEvents(false);
			GetMesh()->SetCollisionProfileName("NoCollision");
			// TODO : ������ �׾ HP ������ ������� ���� Ÿ�̸ӷ� �����ϴ� ���� ���� �� ����
			BossHpWidget->RemoveFromViewport();
		}
		else
		{
			bPhaseChange = true;
			StatusComponent->IncreaseHealth(StatusComponent->GetMaxHp());
			BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());
		}
	}


	return DamageValue;
}

// TODO : ���� ü�� ������ �ٽ� ��������(ü�¼����� �ٽ�)
void ACBoss::ChangePhase()
{
	CheckFalse(bPhaseChange);

	StateComponent->SetAction();
	PlayAnimMontage(PhaseChangeMontage[BossPhase]);

	BossPhase++;
}

void ACBoss::SlashAttack()
{
	CheckFalse(StateComponent->IsIdle());
	StateComponent->SetAction();
	PlayAnimMontage(AttackSlashMontage);
}

void ACBoss::BiteAttack()
{
	CheckFalse(StateComponent->IsIdle());
	StateComponent->SetAction();
	PlayAnimMontage(AttackBiteMontage);
}

void ACBoss::BreathAttack()
{
	CheckFalse(StateComponent->IsIdle());
	StateComponent->SetAction();
	if (bFly == true)
	{
		PlayAnimMontage(FlyFlameMontage);
	}
	else
	{
		PlayAnimMontage(LandFlameMontage);
	}
}
