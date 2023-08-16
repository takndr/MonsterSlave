#include "CInventorySlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Widgets/CInventory.h"
#include "Widgets/CInvenEquip.h"
#include "Widgets/CEquipSlot.h"
#include "Player/CPlayer.h"

#include "Global.h"

bool UCInventorySlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInventorySlot::SettingSlot(FCItemStruct InItem) {
	InvenSlotItem = InItem;
	bFilled = true;

	SlotImage->SetBrushFromTexture(InvenSlotItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UCInventorySlot::EquipItem() {
	CLog::Log("Equiped Item!!");

	// 후에 장비창에 아이템이 채워져있으면 교체하는 형태로 진행
	switch (InvenSlotItem.WeaponType) {
		case EWeaponType::Sword: {
			EquipSword();
			break;
		}
		case EWeaponType::Bow: {
			EquipBow();
			break;
		}
	}

	
}

void UCInventorySlot::EquipSword() {
	CLog::Log("Equip Sword!");
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// 현재는 EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (playertest->InventoryWidget->Equipment->EquipSlotSword->IsEquipped() == true) {
		FCItemStruct temp = playertest->InventoryWidget->Equipment->EquipSlotSword->GetItem();
		playertest->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		playertest->EquipSword(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot에 등록 혹은 EquipSlot에 아이템이 등록되어 있을 경우 교체
		playertest->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		// Player의 Item배열에서 해당 아이템 삭제 혹은 교체된 아이템이 있을 경우 아이템에 추가
		playertest->RemoveItem(InvenSlotItem);
		// 인벤토리 창에서 해당 아이템 제거 및 교체된 아이템이 있을경우 인벤토리에 추가
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// 플레이어에게 실제로 아이템 장착
		playertest->EquipSword(InvenSlotItem);
		bFilled = false;
	}

	
	
}

void UCInventorySlot::EquipBow() {
	CLog::Log("Equip Bow!");
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// 현재는  EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함
	if (playertest->InventoryWidget->Equipment->EquipSlotBow->IsEquipped() == true) {
		FCItemStruct temp = playertest->InventoryWidget->Equipment->EquipSlotBow->GetItem();
		playertest->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		playertest->EquipBow(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot에 등록 혹은 EquipSlot에 아이템이 등록되어 있을 경우 교체
		playertest->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		// Player의 Item배열에서 해당 아이템 삭제 혹은 교체된 아이템이 있을 경우 아이템에 추가
		playertest->RemoveItem(InvenSlotItem);
		// 인벤토리 창에서 해당 아이템 제거 및 교체된 아이템이 있을경우 인벤토리에 추가
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// 플레이어에게 실제로 아이템 장착
		playertest->EquipBow(InvenSlotItem);
		bFilled = false;
	}
}

