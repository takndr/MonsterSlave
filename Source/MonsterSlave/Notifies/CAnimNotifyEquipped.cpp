#include "Notifies/CAnimNotifyEquipped.h"

#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyEquipped::GetNotifyName_Implementation() const {
	return "Equipped";
}

void UCAnimNotifyEquipped::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->Equipped();
}