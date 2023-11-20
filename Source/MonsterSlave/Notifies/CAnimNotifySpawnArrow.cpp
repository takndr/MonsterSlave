#include "Notifies/CAnimNotifySpawnArrow.h"

#include "Items/CEquipItem.h"
#include "Items/Weapons/CEquipBow.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifySpawnArrow::GetNotifyName_Implementation() const {
	return "SpawnArrow";
}

void UCAnimNotifySpawnArrow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	UCItemData* equipItemData = weaponComp->GetCurrentWeapon();
	CheckNull(equipItemData);

	ACEquipItem* equipItem = equipItemData->GetEquipItem();
	CheckNull(equipItem);

	ACEquipBow* bow = Cast<ACEquipBow>(equipItem);
	CheckNull(bow);

	bow->SpawnArrow();
}