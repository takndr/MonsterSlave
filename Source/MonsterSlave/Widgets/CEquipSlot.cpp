#include "Widgets/CEquipSlot.h"

#include "Components/Image.h"

#include "Player/CPlayer.h"

#include "Global.h"


void UCEquipSlot::SettingSlot(FCItemStruct InItem) {
	SlotImage->SetBrushFromTexture(InItem.Picture);

	Item = InItem;
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
	playertest->AddItem(Item);

	

}