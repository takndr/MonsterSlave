#include "Enemy/CBoss.h"

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
	CHelpers::GetAsset(&meshAsset, "SkeletalMesh'/Game/Boss/Asset/FourEvilDragonsPBR/Meshes/DragonTheUsurper/DragonTheUsurperSK.DragonTheUsurperSK'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animClass;
	CHelpers::GetClass(&animClass, "/Game/Boss/ABP_Boss");
	GetMesh()->SetAnimInstanceClass(animClass);

}

void ACBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


