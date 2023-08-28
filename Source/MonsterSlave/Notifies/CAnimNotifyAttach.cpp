#include "Notifies/CAnimNotifyAttach.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"


FString UCAnimNotifyAttach::GetNotifyName_Implementation() const {
	return "Attach";
}

void UCAnimNotifyAttach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(player);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);
	CheckNull(weapon);

	EWeaponType type = weapon->GetWeaponType();
	weapon->Weapons[(int32)type]->Attach();

}