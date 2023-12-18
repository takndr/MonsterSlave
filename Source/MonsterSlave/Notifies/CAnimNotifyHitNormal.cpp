#include "Notifies/CAnimNotifyHitNormal.h"

#include "Items/CEquipItem.h"
#include "Items/CItemData.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyHitNormal::GetNotifyName_Implementation() const {
	return "HitNormal";
}

void UCAnimNotifyHitNormal::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	UCItemData* equipItemData = weaponComp->GetCurrentWeapon();
	CheckNull(equipItemData);

	ACEquipItem* equipItem = equipItemData->GetEquipItem();
	CheckNull(equipItem);

	equipItem->SetHitNormal();
}