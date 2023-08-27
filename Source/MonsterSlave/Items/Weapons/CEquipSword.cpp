#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"

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
	//CheckTrue(GetOwner() == OtherActor);
	//CLog::Print(GetOwner()->GetName());
	//CLog::Print("Sword Attack!!");
}

void ACEquipSword::Attack() {
	CheckNull(AttackMontage);
	CheckNull(AimAttackMontage);
	CheckNull(Owner);
	Super::Attack();

	CLog::Log("Sword Attack");

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage);
	}
	else {
		player->PlayAnimMontage(AttackMontage);
	}
	
}