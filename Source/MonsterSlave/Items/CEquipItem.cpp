#include "CEquipItem.h"

#include "GameFramework/Character.h"

#include "Global.h"

ACEquipItem::ACEquipItem() {
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "Mesh", Scene);
}

void ACEquipItem::BeginPlay() {
	Super::BeginPlay();

}

void ACEquipItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}
