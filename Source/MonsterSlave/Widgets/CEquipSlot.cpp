#include "Widgets/CEquipSlot.h"

#include "Components/Image.h"

#include "Player/CPlayer.h"

#include "Global.h"


void UCEquipSlot::SettingSlot(FCItemStruct InItem) {
	SlotImage->SetBrushFromTexture(InItem.Picture);

	EquipSlotItem = InItem;
	bEquipped = true;
}

bool UCEquipSlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(DefaultImage, false);
	SlotImage->SetBrushFromTexture(DefaultImage);

	return true;
}

void UCEquipSlot::UnEquipItem() {
	bEquipped = false;

	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	playertest->AddItem(EquipSlotItem);

	SlotImage->SetBrushFromTexture(DefaultImage);

	switch (EquipSlotItem.WeaponType) {
		case EWeaponType::Sword: {
			playertest->UnEquipSword();
			break;
		}
		case EWeaponType::Bow: {
			playertest->UnEquipBow();
			break;
		}
	}
}

void UCEquipSlot::UnEquipSword() {
	// 플레이어에게 장착된 부분 해제

}

void UCEquipSlot::UnEquipBow() {
	// 플레이어에게 장착된 부분 해제

}