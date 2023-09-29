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

	// TODO : 보스전용 체력 위젯 만들기
	BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	// 데미지 보여주기
	// TODO : damageTransform 수정
	FTransform damageTransform = GetActorTransform();
	ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(ACDamageText::StaticClass(), damageTransform);
	damageText->FinishSpawning(damageTransform);
	damageText->SetDamageText(Damage);

	// 체력 전부 줄으면 페이즈 전환 / 마지막 페이즈라면 보스 사망
	if (StatusComponent->IsDead())
	{
		// TODO : 현재 마지막 페이즈인지는 하드코딩으로 넣어 놓았음
		if (BossPhase == 2)
		{
			PlayAnimMontage(DieMontage);
			GetMesh()->SetGenerateOverlapEvents(false);
			GetMesh()->SetCollisionProfileName("NoCollision");
			// TODO : 보스가 죽어서 HP 위젯이 사라지는 것을 타이머로 설정하는 것이 나을 것 같음
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

// TODO : 보스 체력 위젯이 다시 차오르게(체력설정도 다시)
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
