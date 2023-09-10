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
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	CheckTrue(OtherActor == Owner);
	
	// TODO : �ٴ���Ʈ ���� �ȵǰ� HittedActors�� TArray�� �����Ͽ� ��������
	// ���� Collision�� ������ �ٸ� Actor�� HittedActors�迭�� ���� ��� return�Ͽ� �ڵ� �� ���� ���ϰ�
	if (HittedActors.Find(OtherActor) != -1) {
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : ������ �ٶ� ��������Ʈ�ؼ� actor���� �ٸ� ȿ�� �Ͼ���� �����ϸ� ������ �� ���⵵ ��
	// ������ ������ �ֱ�
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
