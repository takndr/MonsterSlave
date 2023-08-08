#include "CEquipItem.h"

#include "Global.h"

ACEquipItem::ACEquipItem() {
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "Mesh");
}

void ACEquipItem::BeginPlay() {
	Super::BeginPlay();

}

void ACEquipItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

