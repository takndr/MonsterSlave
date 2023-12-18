#include "Notifies/CAnimNotifyHitKnockBack.h"

#include "Items/CEquipItem.h"
#include "Items/CItemData.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyHitKnockBack::GetNotifyName_Implementation() const {
	return "HitKnockBack";
}

void UCAnimNotifyHitKnockBack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	UCItemData* equipItemData = weaponComp->GetCurrentWeapon();
	CheckNull(equipItemData);

	ACEquipItem* equipItem = equipItemData->GetEquipItem();
	CheckNull(equipItem);

	equipItem->SetHitKnockBack();
}