#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

#include "Player/CPlayer.h"
#include "Player/Skill/CArrowRain.h"
#include "Component/CStateComponent.h"
#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACEquipBow::ACEquipBow()
{
	WeaponType = EWeaponType::Bow;
	StaticMesh->SetRelativeLocation(FVector(0.365274f, -5.794907f, -3.626544f));
	StaticMesh->SetRelativeRotation(FRotator(-7.968262f, 77.989388f, -23.575928f));

	CHelpers::GetClass(&ArrowClass, "/Game/Items/Weapons/Arrow/BP_Arrow");
	CHelpers::GetClass(&ArrowRainClass, "/Game/Items/Weapons/Arrow/BP_ArrowRain");
}

void ACEquipBow::BeginPlay()
{
	Super::BeginPlay();

}

void ACEquipBow::Attack()
{
	Super::Attack();

}

void ACEquipBow::FirstSkill()
{
	Super::FirstSkill();

}

void ACEquipBow::SecondSkill()
{
	Super::SecondSkill();
	
	UKismetSystemLibrary::K2_SetTimer(this, "SpawnArrowRain", 2.0f, false);
}

void ACEquipBow::SpawnArrow()
{
	FTransform transform = Owner->GetMesh()->GetSocketTransform("bow_socket");
	ACPlayer* player = Cast<ACPlayer>(Owner);

	//transform.SetRotation(FQuat(Owner->GetActorForwardVector().Rotation()));
	transform.SetRotation(FQuat(player->GetMeshCamera()->GetForwardVector().Rotation()));
	Arrow = GetWorld()->SpawnActorDeferred<ACArrow>(ArrowClass, transform, Owner);

	Arrow->FinishSpawning(transform);
}

void ACEquipBow::SpawnArrowRain()
{
	FVector location = Owner->GetActorLocation() + Owner->GetActorForwardVector() * ArrowRainRange + Owner->GetActorUpVector() * 500;
	FTransform transform;
	transform.SetLocation(location);

	FActorSpawnParameters spawnParameter;
	spawnParameter.Owner = Owner;

	GetWorld()->SpawnActor<ACArrowRain>(ArrowRainClass, transform, spawnParameter);
}

