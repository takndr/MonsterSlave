#include "CInventorySlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Widgets/Inventory/CInventory.h"
#include "Widgets/Inventory/CEquipSlot.h"
#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

bool UCInventorySlot::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInventorySlot::SettingSlot(FCItemStruct InItem)
{
	InvenSlotItem = InItem;
	bFilled = true;

	SlotImage->SetBrushFromTexture(InvenSlotItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UCInventorySlot::EquipItem()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Inventory = player->GetInventory();

	switch (InvenSlotItem.WeaponType)
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
	CLog::Log("Equip Sword!");
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// 현재는 EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (weaponComp->IsSetSword())
	{
		weaponComp->RemoveSword();
		FCItemStruct temp = Inventory->SwordEquipment->GetItem();
		player->ReplaceInventoryItem(InvenSlotItem, temp);
		Inventory->SwordEquipment->SettingSlot(InvenSlotItem);
		
		weaponComp->SetSword(InvenSlotItem);
		SettingSlot(temp);
	}
	else
	{
		Inventory->SwordEquipment->SettingSlot(InvenSlotItem);
		player->RemoveInventoryItem(InvenSlotItem);
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		weaponComp->SetSword(InvenSlotItem);
		bFilled = false;
	}	
}

void UCInventorySlot::EquipBow()
{
	CLog::Log("Equip Bow!");
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// 현재는  EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (weaponComp->IsSetBow())
	{
		weaponComp->RemoveBow();
		FCItemStruct temp = Inventory->BowEquipment->GetItem();
		player->ReplaceInventoryItem(InvenSlotItem, temp);
		Inventory->BowEquipment->SettingSlot(InvenSlotItem);
		weaponComp->SetBow(InvenSlotItem);
		SettingSlot(temp);
	}
	else
	{
		Inventory->BowEquipment->SettingSlot(InvenSlotItem);
		player->RemoveInventoryItem(InvenSlotItem);
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		weaponComp->SetBow(InvenSlotItem);
		bFilled = false;
	}
}

