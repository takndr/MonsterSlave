#include "CInventory.h"

#include "Components/UniformGridPanel.h"
#include "GameFramework/Character.h"

#include "Widgets/Inventory/CInventorySlot.h"
#include "Widgets/Inventory/CEquipSlot.h"
#include "Player/CPlayer.h"
#include "GameMode/CSaveGame.h"

#include "Global.h"

void UCInventory::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());

	Update();
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

// 처음 가방 초기화
void UCInventory::Update()
{
	// 저장된 정보 있으면 저장
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	CheckNull(saveGame);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	
	for (uint8 i = 0; i < saveGame->Items.Num(); i++)
	{
		AddItem(saveGame->Items[i]);
	}

	if (saveGame->SwordItem.Name != "NULL")
	{
		SwordEquipment->SettingSlot((saveGame->SwordItem));
	}

	if (saveGame->BowItem.Name != "NULL")
	{
		BowEquipment->SettingSlot((saveGame->BowItem));
	}
}

// 아이템 먹었을 때 실행
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
