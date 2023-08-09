#include "CInventorySlot.h"

#include "Components/Button.h"

#include "Global.h"

bool UCInventorySlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(SlotButton, false);
	// clicked event 바인딩
	SlotButton->OnClicked.AddDynamic(this, &UCInventorySlot::Clicked);

	return true;
}

void UCInventorySlot::Clicked() {
	CLog::Log("Item Clicked");
	// 마우스 우측버튼으로 클릭시
}


