#include "CInventory.h"

#include "Components/UniformGridPanel.h"

#include "CInventorySlot.h"

#include "Global.h"

UCInventory::UCInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

bool UCInventory::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInventory::Attach() {
	CLog::Log("Inventory Opened!!");

	Opened = true;
	SetVisibility(ESlateVisibility::Visible);

	bIsFocusable = true;

	FInputModeGameAndUI inputMode;
	//FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetHideCursorDuringCapture(true);

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);
}

void UCInventory::Detach() {
	CLog::Log("Inventory Closed!!");

	Opened = false;
	SetVisibility(ESlateVisibility::Collapsed);

	bIsFocusable = false;

	FInputModeGameOnly inputMode;
	
	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);
}

// 처음 가방 초기화
void UCInventory::Update() {


}

// 아이템 먹었을 때 실행
uint32 UCInventory::AddItem(FCItemStruct item) {
	for (uint32 i = 0; i < MaxInventory; i++) {
		UCInventorySlot* slot = Cast<UCInventorySlot>(BagPannel->GetChildAt(i));
		if (slot->IsFilled() == false) {
			slot->SettingSlot(item);
			return i;
		}
	}

	return -1;
}
