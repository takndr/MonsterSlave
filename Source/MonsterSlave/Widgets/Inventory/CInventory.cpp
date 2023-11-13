#include "CInventory.h"

#include "Components/UniformGridPanel.h"

#include "Widgets/Inventory/CInventorySlot.h"

#include "Global.h"

bool UCInventory::Initialize()
{
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInventory::Attach()
{
	Opened = true;
	SetVisibility(ESlateVisibility::Visible);

	bIsFocusable = true;

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetHideCursorDuringCapture(true);

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);
}

void UCInventory::Detach()
{
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

// ó�� ���� �ʱ�ȭ
void UCInventory::Update()
{


}

// ������ �Ծ��� �� ����
uint32 UCInventory::AddItem(FCItemStruct item)
{
	for (uint32 i = 0; i < MaxInventory; i++)
	{
		UCInventorySlot* slot = Cast<UCInventorySlot>(BagPannel->GetChildAt(i));
		if (slot->IsFilled() == false)
		{
			slot->SettingSlot(item);
			return i;
		}
	}

	return -1;
}
