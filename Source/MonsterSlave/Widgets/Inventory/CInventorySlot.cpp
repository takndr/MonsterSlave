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

void UCInventorySlot::SettingSlot(FCItemStruct InItem)
{
	InvenSlotItem = InItem;
	bFilled = true;

	SlotImage->SetBrushFromTexture(InvenSlotItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
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
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// ����� EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
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
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);

	// ����� EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
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

