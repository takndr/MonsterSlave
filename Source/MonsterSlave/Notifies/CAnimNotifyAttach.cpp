#include "Notifies/CAnimNotifyAttach.h"

#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyAttach::GetNotifyName_Implementation() const {
	return "Attach";
}

void UCAnimNotifyAttach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->Attach();
}