#include "Items/CItemData.h"

#include "GameFramework/Character.h"

#include "Items/CEquipItem.h"

#include "Global.h"

void UCItemData::SpawnEquipItem(UWorld* InWorld, ACharacter* OwnerCharacter)
{
	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	EquipItem = InWorld->SpawnActor<ACEquipItem>(Item.EquipWeaponClass, param);
	EquipItem->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, EquipItem->UnEquippedHolster);
}