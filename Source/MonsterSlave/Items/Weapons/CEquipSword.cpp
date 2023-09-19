#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Global.h"

// TODO6 : EquipSword들 Collision 위치 조정
// TODO7 : HittedActor를 OffCollision쪽에 초기화를 진행해두었는데, 이 위치가 맞는지 다시 한번 고심해서 재조정

ACEquipSword::ACEquipSword() {
	WeaponType = EWeaponType::Sword;
	CHelpers::CreateSceneComponent(this, &Capsule, "Collision", SkeletalMesh);
}

void ACEquipSword::BeginPlay() {
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEquipSword::OnOverlap);
}

void ACEquipSword::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// 여러 조건 붙이고 통과하면 진행 -> 본인과 Owner 제외
	CheckTrue(OtherActor == Owner);
	
	if (HittedActors.Find(OtherActor) != -1) {
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : 데미지 줄때 델리게이트해서 actor마다 다른 효과 일어나도록 진행하면 괜찮을 것 같기도 함
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(30.0f, damageEvent, Owner->GetController(), this);

	// TODO : Damage Effect


	// TODO : Damage Widget
}

void ACEquipSword::Attack()
{
	Super::Attack();

	CheckTrue(AimAttackMontage.Num() == 0);
	CheckTrue(AttackMontage.Num() == 0);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;
		return;
	}

	CheckFalse(StateComp->IsIdle());

	StateComp->SetAction();

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim())
	{
		player->PlayAnimMontage(AimAttackMontage[ComboCount]);
	}
	else
	{
		player->PlayAnimMontage(AttackMontage[ComboCount]);
	}
}

void ACEquipSword::EndAttack() {
	Super::EndAttack();
	
	StateComp->SetIdle();
	ComboCount = 0;
}

void ACEquipSword::NextCombo() {
	CheckFalse(bSucceed);
	bSucceed = false;
	ComboCount++;

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage[ComboCount]);
	}
	else {
		player->PlayAnimMontage(AttackMontage[ComboCount]);
	}
}

void ACEquipSword::OnCollision() {
	CheckNull(Capsule);

	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEquipSword::OffCollision() {
	CheckNull(Capsule);

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HittedActors.Empty();
	HittedActors.Shrink();
}
