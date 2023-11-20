#include "Notifies/CAnimNotifyDetach.h"

#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyDetach::GetNotifyName_Implementation() const {
	return "Detach";
}

void UCAnimNotifyDetach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	UCItemData* equipItemData = weaponComp->GetCurrentWeapon();
	CheckNull(equipItemData);

	ACEquipItem* equipItem = equipItemData->GetEquipItem();
	CheckNull(equipItem);

	equipItem->Detach();
}