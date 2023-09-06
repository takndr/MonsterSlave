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

	// ü�� ���� �پ���
	// TODO : �������� ü�� ���� �����
	// 
	// ���� ü���� �� ��Ƽ� 0�̵Ǹ� �״� �ŷ� ó��
	if (Status->IsDead()) {

	}

	// ü���� ���� �κб��� ������ ������ ��ȯ
	


	return DamageValue;
}

