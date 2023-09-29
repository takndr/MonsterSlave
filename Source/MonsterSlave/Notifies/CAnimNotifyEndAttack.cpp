#include "Notifies/CAnimNotifyEndAttack.h"

#include "Component/CWeaponComponent.h"
#include "Component/CStateComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const {
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	// TODO : Boss도 이용 가능하게 진행했는데, 구조를 전체적으로 바꿔야함
	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);
	stateComp->SetIdle();

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->EndAttack();
}
