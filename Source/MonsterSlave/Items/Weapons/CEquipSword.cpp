#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Global.h"

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
	
	// TODO : 다단히트 생성 안되게 HittedActors의 TArray를 생성하여 방지하자
	// 현재 Collision이 접촉한 다른 Actor가 HittedActors배열에 있을 경우 return하여 코드 더 진행 못하게
	if (HittedActors.Find(OtherActor) != -1) {
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : 데미지 줄때 델리게이트해서 actor마다 다른 효과 일어나도록 진행하면 괜찮을 것 같기도 함
	// 적에게 데미지 주기
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(30.0f, damageEvent, Owner->GetController(), this);
}

void ACEquipSword::Attack() {
	Super::Attack();

	CheckTrue(AimAttackMontage.Num() == 0);
	CheckTrue(AttackMontage.Num() == 0);

	if (bCanCombo == true) {
		bCanCombo = false;
		bSucceed = true;
		return;
	}

	CheckFalse(StateComp->IsIdle());

	StateComp->SetAttack();

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage[ComboCount]);
	}
	else {
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
