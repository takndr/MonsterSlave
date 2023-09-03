#include "Notifies/CAnimNotifyEndAttack.h"

#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

// ComboCount
FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const {
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);
	stateComp->SetIdle();

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);
	weaponComp->GetCurrentWeapon()->ComboCount = 0;
}
// 활 EndAttack같은 경우에는 화살까지 재스폰 시켜야함