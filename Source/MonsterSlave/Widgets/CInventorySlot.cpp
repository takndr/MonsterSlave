#include "CInventorySlot.h"

#include "Components/Button.h"

#include "CItemDescription.h"

#include "Global.h"

bool UCInventorySlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(SlotButton, false);
	// clicked event 바인딩
	SlotButton->OnClicked.AddDynamic(this, &UCInventorySlot::Clicked);
	// hovered event 바인딩
	SlotButton->OnHovered.AddDynamic(this, &UCInventorySlot::Hovered);
	// unhovered event 바인딩
	SlotButton->OnUnhovered.AddDynamic(this, &UCInventorySlot::UnHovered);

	return true;
}

void UCInventorySlot::Clicked() {
	CLog::Log("Item Clicked");
}

void UCInventorySlot::Hovered() {
	CLog::Log("Item Hovered");

	//Description->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCInventorySlot::UnHovered() {
	CLog::Log("Item UnHovered");

	//Description->SetVisibility(ESlateVisibility::Collapsed);


}


