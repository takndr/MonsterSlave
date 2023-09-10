#include "Notifies/CAnimNotifyEndAttack.h"

#include "Component/CWeaponComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

// ComboCount
FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const {
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->EndAttack();
}
// Ȱ EndAttack���� ��쿡�� ȭ����� �罺�� ���Ѿ���