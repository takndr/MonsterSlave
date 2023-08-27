#include "Notifies/CAnimNotifyNextCombo.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"

#include "Global.h"


FString UCAnimNotifyNextCombo::GetNotifyName_Implementation() const {
	return "NextCombo";
}

void UCAnimNotifyNextCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);


}