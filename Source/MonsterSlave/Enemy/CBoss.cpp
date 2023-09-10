#include "Enemy/CBoss.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "Component/CStatusComponent.h"
#include "Widgets/CBossHp.h"

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
}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();
	BossHpWidget = CreateWidget<UCBossHp>(GetWorld(), BossHpWidgetClass);
	BossHpWidget->AddToViewport();

	CheckNull(BossHpWidget);
	BossHpWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBoss::BossFly()
{
	CLog::Print("Fly");
	//GetMesh()->GetAnimInstance()->Montage_Play(FlyMontage);
	PlayAnimMontage(FlyMontage);
}

void ACBoss::BossLand()
{
	CLog::Print("Land");
	//GetMesh()->GetAnimInstance()->Montage_Play(LandMontage);
	PlayAnimMontage(LandMontage);
}

float ACBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	StatusComponent->DecreaseHealth(DamageValue);
	CLog::Print(DamageValue);
	// 체력 위젯 줄어들게
	// TODO : 보스전용 체력 위젯 만들기
	BossHpWidget->UpdateHealth(StatusComponent->GetCurrentHp(), StatusComponent->GetMaxHp());

	// 만약 체력이 다 닳아서 0이되면 죽는 거로 처리
	if (StatusComponent->IsDead()) {
		PlayAnimMontage(DieMontage);
		GetMesh()->SetGenerateOverlapEvents(false);
		GetMesh()->SetCollisionProfileName("NoCollision");
	}

	// 체력이 일정 부분까지 줄으면 페이즈 전환
	


	return DamageValue;
}

