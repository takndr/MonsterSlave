#include "Notifies/CAnimNotifyStateCollision.h"

#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"
#include "Component/CWeaponComponent.h"
#include "Items/Weapons/CEquipSword.h"
#include "Items/CItemData.h"

#include "Global.h"

FString UCAnimNotifyStateCollision::GetNotifyName_Implementation() const {
	return "Collision";
}

void UCAnimNotifyStateCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Player老 版快
	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
		CheckNull(weaponComp);

		UCItemData* swordData = weaponComp->GetCurrentWeapon();
		CheckNull(swordData);

		ACEquipSword* swordEquip = Cast<ACEquipSword>(swordData->GetEquipItem());
		CheckNull(swordEquip);

		swordEquip->OnCollision();
	}

	// Boss老 版快
	if (!!Cast<ACBoss>(MeshComp->GetOwner()))
	{
		CheckTrue(CollisionName == "None");

		ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());

		boss->OnCollision(CollisionName);
	}
	
	if (!!Cast<ACDummyEnemy>(MeshComp->GetOwner()))
	{
		ACDummyEnemy* enemy = Cast<ACDummyEnemy>(MeshComp->GetOwner());
		CheckNull(enemy);

		enemy->OnCollision();
	}
}

void UCAnimNotifyStateCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);

	// Player老 版快
	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
		CheckNull(weaponComp);

		UCItemData* swordData = weaponComp->GetCurrentWeapon();
		CheckNull(swordData);

		ACEquipSword* swordEquip = Cast<ACEquipSword>(swordData->GetEquipItem());
		CheckNull(swordEquip);

		swordEquip->OffCollision();
	}

	// Boss老 版快
	if (!!Cast<ACBoss>(MeshComp->GetOwner()))
	{
		CheckTrue(CollisionName == "None");

		ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
		boss->OffCollision(CollisionName);

		boss->SetHeavyHit(false);
		boss->ClearHittedCharacters();
	}

	if (!!Cast<ACDummyEnemy>(MeshComp->GetOwner()))
	{
		ACDummyEnemy* enemy = Cast<ACDummyEnemy>(MeshComp->GetOwner());
		CheckNull(enemy);

		enemy->OffCollision();
	}
}