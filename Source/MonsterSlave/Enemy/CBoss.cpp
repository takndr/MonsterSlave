#include "Enemy/CBoss.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "Component/CStatusComponent.h"

#include "Global.h"

ACBoss::ACBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);
	
	//
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/Boss/_Asset/Meshes/DragonTheUsurperSK");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animClass;
	CHelpers::GetClass(&animClass, "/Game/Boss/ABP_Boss");
	GetMesh()->SetAnimInstanceClass(animClass);

	//
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ACBoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Status->DecreaseHealth(DamageValue);

	// 체력 위젯 줄어들게
	// TODO : 보스전용 체력 위젯 만들기
	// 
	// 만약 체력이 다 닳아서 0이되면 죽는 거로 처리
	if (Status->IsDead()) {

	}

	// 체력이 일정 부분까지 줄으면 페이즈 전환
	


	return DamageValue;
}

