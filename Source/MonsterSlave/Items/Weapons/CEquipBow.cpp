#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACEquipBow::ACEquipBow() {
	WeaponType = EWeaponType::Bow;
	StaticMesh->SetRelativeLocation(FVector(0.365274f, -5.794907f, -3.626544f));
	StaticMesh->SetRelativeRotation(FRotator(-7.968262f, 77.989388f, -23.575928f));
}

void ACEquipBow::BeginPlay() {
	Super::BeginPlay();

}

void ACEquipBow::Attack()
{
	Super::Attack();

}

void ACEquipBow::Equipped() {
	Super::Equipped();

	// 활에 화살 붙이기
	// SpawnArrow();
}

void ACEquipBow::UnEquipped() {
	Super::UnEquipped();

	// 활에 화살 붙이기
	//if (Arrow != nullptr) {
	//	Arrow->Destroy();
	//	Arrow = nullptr;
	//}
}

void ACEquipBow::ShotArrow() {
	CheckNull(Arrow);

	Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Arrow->ShootArrow();
}

void ACEquipBow::SpawnArrow() {
	//FTransform transform = SkeletalMesh->GetSocketTransform("arrow_socket");
	//Arrow = GetWorld()->SpawnActorDeferred<ACArrow>(ArrowClass, transform, Owner);
	//Arrow->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, "arrow_socket");
	//Arrow->FinishSpawning(transform);
}