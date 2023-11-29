#include "CEquipSlot.h"

#include "Components/Image.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"
#include "Items/CItemData.h"

#include "Global.h"

void UCEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	SlotImage->SetBrushFromTexture(DefaultImage);
}

void UCEquipSlot::SettingSlot(class UCItemData* InItem)
{
	SlotImage->SetBrushFromTexture(InItem->Item.Picture);

	Item = InItem;
	bEquipped = true;
}

void UCEquipSlot::UnEquipItem()
{
	bEquipped = false;

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);

	player->AddItem(Item);
	SlotImage->SetBrushFromTexture(DefaultImage);

	switch (Item->Item.WeaponType)
	{
		case EWeaponType::Sword: 
		{
			weapon->RemoveSword();
			break;
		}
		case EWeaponType::Bow:
		{
			weapon->RemoveBow();
			break;
		}
	}
}
