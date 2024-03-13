#include "Notifies/CAnimNotifyStateCollision.h"

#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"
#include "Component/CWeaponComponent.h"
#include "Items/CEquipitem.h"
#include "Items/CItemData.h"

#include "Global.h"

FString UCAnimNotifyStateCollision::GetNotifyName_Implementation() const {
	return "Collision";
}

void UCAnimNotifyStateCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Player�� ���
	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
		CheckNull(weaponComp);

		UCItemData* weaponData = weaponComp->GetCurrentWeapon();
		CheckNull(weaponData);

		ACEquipItem* weaponEquip = Cast<ACEquipItem>(weaponData->GetEquipItem());
		CheckNull(weaponEquip);

		weaponEquip->OnCollision();
	}

	// Boss�� ���
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

	// Player�� ���
	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
		CheckNull(weaponComp);

		UCItemData* weaponData = weaponComp->GetCurrentWeapon();
		CheckNull(weaponData);

		ACEquipItem* weaponEquip = Cast<ACEquipItem>(weaponData->GetEquipItem());
		CheckNull(weaponEquip);

		weaponEquip->OffCollision();
	}

	// Boss�� ���
	if (!!Cast<ACBoss>(MeshComp->GetOwner()))
	{
		CheckTrue(CollisionName == "None");

		ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
		boss->OffCollision(CollisionName);

		boss->ClearHittedCharacters();
	}

	if (!!Cast<ACDummyEnemy>(MeshComp->GetOwner()))
	{
		ACDummyEnemy* enemy = Cast<ACDummyEnemy>(MeshComp->GetOwner());
		CheckNull(enemy);

		enemy->OffCollision();
	}
}