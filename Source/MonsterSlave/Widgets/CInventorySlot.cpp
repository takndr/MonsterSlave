#include "CInventorySlot.h"

#include "Components/Button.h"

#include "Global.h"

bool UCInventorySlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(SlotButton, false);
	// clicked event ���ε�
	SlotButton->OnClicked.AddDynamic(this, &UCInventorySlot::Clicked);

	return true;
}

void UCInventorySlot::Clicked() {
	CLog::Log("Item Clicked");
	// ���콺 ������ư���� Ŭ����
}


