#include "CInventory.h"

#include "Components/UniformGridPanel.h"

#include "CInventorySlot.h"

#include "Global.h"

UCInventory::UCInventory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	CHelpers::GetClass(&Slot, "/Game/Widgets/Widget/Inventory/WB_Inventory_Slot");
}

bool UCInventory::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return false;
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
void UCInventory::AddItem(FCItemStruct item) {
	UCInventorySlot* invenslot = CreateWidget<UCInventorySlot>(GetWorld(), Slot);

	invenslot->SettingSlot(item);
	invenslot->SetVisibility(ESlateVisibility::Visible);

	BagPannel->AddChildToUniformGrid(invenslot, CurrentRow, CurrentColumn);
	SetRowColumn();
}

void UCInventory::SetRowColumn() {
	CLog::Log("Column : " + FString::FromInt(CurrentColumn) + ", Row : " + FString::FromInt(CurrentRow));

	if (CurrentColumn + 1 >= MaxInColumn) {
		CurrentColumn = 0;
		CurrentRow++;
	}
	else {
		CurrentColumn++;
	}
	
}