#include "Notifies/CAnimNotifyUnEquipped.h"

#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyUnEquipped::GetNotifyName_Implementation() const {
	return "UnEquipped";
}

void UCAnimNotifyUnEquipped::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

}