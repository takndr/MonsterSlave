#include "Notifies/CAnimNotifyNextCombo.h"

#include "Component/CWeaponComponent.h"
#include "Items/CEquipItem.h"
#include "Items/Weapons/CEquipSword.h"

#include "Global.h"

FString UCAnimNotifyNextCombo::GetNotifyName_Implementation() const {
	return "NextCombo";
}

void UCAnimNotifyNextCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);
	
	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	ACEquipSword* swordItem = Cast<ACEquipSword>(equipItem);
	swordItem->NextCombo();
}