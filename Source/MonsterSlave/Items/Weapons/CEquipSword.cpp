#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"

#include "Global.h"

ACEquipSword::ACEquipSword() {

	CHelpers::CreateSceneComponent(this, &Capsule, "Collision", SkeletalMesh);
}

void ACEquipSword::BeginPlay() {
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEquipSword::OnOverlap);
}

void ACEquipSword::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	CLog::Print("Sword Attack!!");
}