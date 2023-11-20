#include "CInventorySlot.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "GameFramework/Character.h"

#include "Widgets/Inventory/CInventory.h"
#include "Widgets/Inventory/CEquipSlot.h"
#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"
#include "Items/CItemData.h"

#include "Global.h"

void UCInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	Inventory = player->GetInventory();
}

void UCInventorySlot::SettingSlot(class UCItemData* InItem)
{
	Item = InItem;
	bFilled = true;

	SlotImage->SetBrushFromTexture(Item->Item.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UCInventorySlot::EquipItem()
{
	switch (Item->Item.WeaponType)
	{
		case EWeaponType::Sword:
		{
			EquipSword();
			break;
		}
		case EWeaponType::Bow:
		{
			EquipBow();
			break;
		}
	}	
}

void UCInventorySlot::EquipSword()
{
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// 현재는 EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (weaponComp->IsSetSword())
	{
		weaponComp->RemoveSword();
		UCItemData* temp = Inventory->SwordEquipment->GetItem();
		player->ReplaceInventoryItem(Item, temp);
		Inventory->SwordEquipment->SettingSlot(Item);
		
		weaponComp->SetSword(Item);
		SettingSlot(temp);
	}
	else
	{
		Inventory->SwordEquipment->SettingSlot(Item);
		player->RemoveInventoryItem(Item);
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		weaponComp->SetSword(Item);
		bFilled = false;
	}	
}

void UCInventorySlot::EquipBow()
{
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// 현재는 EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (weaponComp->IsSetBow())
	{
		weaponComp->RemoveBow();
		UCItemData* temp = Inventory->BowEquipment->GetItem();
		player->ReplaceInventoryItem(Item, temp);
		Inventory->BowEquipment->SettingSlot(Item);
		weaponComp->SetBow(Item);
		SettingSlot(temp);
	}
	else
	{
		Inventory->BowEquipment->SettingSlot(Item);
		player->RemoveInventoryItem(Item);
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		weaponComp->SetBow(Item);
		bFilled = false;
	}
}

