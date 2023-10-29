#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACEquipBow::ACEquipBow() {
	WeaponType = EWeaponType::Bow;
	StaticMesh->SetRelativeLocation(FVector(0.365274f, -5.794907f, -3.626544f));
	StaticMesh->SetRelativeRotation(FRotator(-7.968262f, 77.989388f, -23.575928f));

	CHelpers::GetClass(&ArrowClass, "/Game/Items/Weapons/Arrow/BP_Arrow");
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

void ACEquipBow::SpawnArrow() {
	FTransform transform = Owner->GetMesh()->GetSocketTransform("bow_socket");
	ACPlayer* player = Cast<ACPlayer>(Owner);

	//transform.SetRotation(FQuat(Owner->GetActorForwardVector().Rotation()));
	transform.SetRotation(FQuat(player->GetMeshCamera()->GetForwardVector().Rotation()));
	//Arrow = GetWorld()->SpawnActorDeferred<ACArrow>(ArrowClass, transform, Owner);
	Arrow = GetWorld()->SpawnActorDeferred<AActor>(ArrowClass, transform, Owner);

	Arrow->FinishSpawning(transform);
}