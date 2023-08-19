#include "Notifies/CAnimNotifyDetach.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"

#include "Global.h"


FString UCAnimNotifyDetach::GetNotifyName_Implementation() const {
	return "Detach";
}

void UCAnimNotifyDetach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	ACEquipItem* equipItem = Cast<ACEquipItem>(player->GetCurrentWeapon());
	CheckNull(equipItem);

	equipItem->Detach();

}