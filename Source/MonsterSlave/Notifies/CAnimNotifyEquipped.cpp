#include "Notifies/CAnimNotifyEquipped.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"

#include "Global.h"


FString UCAnimNotifyEquipped::GetNotifyName_Implementation() const {
	return "Equipped";
}

void UCAnimNotifyEquipped::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	ACEquipItem* equipItem = Cast<ACEquipItem>(player->GetCurrentWeapon());
	CheckNull(equipItem);

	equipItem->Equipped();
}