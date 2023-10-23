#include "CEquipSlot.h"

#include "Components/Image.h"

#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

void UCEquipSlot::SettingSlot(FCItemStruct InItem)
{
	SlotImage->SetBrushFromTexture(InItem.Picture);

	EquipSlotItem = InItem;
	bEquipped = true;
}

bool UCEquipSlot::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(DefaultImage, false);
	SlotImage->SetBrushFromTexture(DefaultImage);

	return true;
}

void UCEquipSlot::UnEquipItem()
{
	bEquipped = false;

	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);

	player->AddItem(EquipSlotItem);
	SlotImage->SetBrushFromTexture(DefaultImage);

	switch (EquipSlotItem.WeaponType)
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
