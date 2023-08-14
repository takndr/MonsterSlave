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
	SlotImage->SetBrushFromTexture(InItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	InvenItem = InItem;
	bFilled = true;
}

void UCInventorySlot::EquipItem() {
	CLog::Log("Equiped Item!!");

	// 후에 장비창에 아이템이 채워져있으면 교체하는 형태로 진행
	switch (InvenItem.WeaponType) {
		case EWeaponType::Sword: {
			EquipSword();
			break;
		}
		case EWeaponType::Bow: {
			EquipBow();
			break;
		}
	}

	bFilled = false;
}

void UCInventorySlot::EquipSword() {
	CLog::Log("Equip Sword!");
	
	// 현재는  EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함

	// EquipSlot에 등록 혹은 EquipSlot에 아이템이 등록되어 있을 경우 교체
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	playertest->InventoryWidget->Equipment->Sword->SettingSlot(InvenItem);

	// Player의 Item배열에서 해당 아이템 삭제 혹은 교체된 아이템이 있을 경우 아이템에 추가
	playertest->RemoveItem(InvenItem);

	// 인벤토리 창에서 해당 아이템 제거 및 교체된 아이템이 있을경우 인벤토리에 추가
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
}

void UCInventorySlot::EquipBow() {
	CLog::Log("Equip Bow!");

	// 현재는  EquipSlot이 비어있다 가정하고 진행하지만, 만약 EquipSlot에 아이템이 들어가있으면, 교체로 진행해야함

	// EquipSlot에 등록 혹은 EquipSlot에 아이템이 등록되어 있을 경우 교체
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	playertest->InventoryWidget->Equipment->Bow->SettingSlot(InvenItem);

	// Player의 Item배열에서 해당 아이템 삭제 혹은 교체된 아이템이 있을 경우 아이템에 추가
	playertest->RemoveItem(InvenItem);

	// 인벤토리 창에서 해당 아이템 제거 및 교체된 아이템이 있을경우 인벤토리에 추가
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
}

