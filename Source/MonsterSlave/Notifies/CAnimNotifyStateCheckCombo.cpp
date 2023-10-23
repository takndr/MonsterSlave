#include "Notifies/CAnimNotifyStateCheckCombo.h"

#include "Component/CWeaponComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

FString UCAnimNotifyStateCheckCombo::GetNotifyName_Implementation() const {
	return "CheckCombo";
}

void UCAnimNotifyStateCheckCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->EnabledCombo();
}

void UCAnimNotifyStateCheckCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->DisabledCombo();
}