#include "Notifies/CAnimNotifyUnEquipped.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

FString UCAnimNotifyUnEquipped::GetNotifyName_Implementation() const {
	return "UnEquipped";
}

void UCAnimNotifyUnEquipped::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);
	CheckNull(weapon);

	ACEquipItem* equipItem = weapon->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->UnEquipped();
}