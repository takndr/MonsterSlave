#include "Widgets/MainMenu/CMainMenu.h"

#include "Components/Border.h"
#include "Components/Image.h"

#include "GameMode/CSaveGame.h"

#include "Global.h"

void UCMainMenu::NativeConstruct()
{
	MenuBorder->OnMouseButtonDownEvent.BindUFunction(this, "Connect");
	OptionImage->OnMouseButtonDownEvent.BindUFunction(this, "OpenOptionMenu");
}

void UCMainMenu::Connect()
{
	// save���� �����ͼ� ����� ���� ������ ������� �˾Ƴ���
	// �ش� ������ �̵�
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	FString map;

	if (saveGame != nullptr)
	{
		CLog::Log("Load Game" + saveGame->CurrentLevelName);
		map = "/Game/Maps/" + saveGame->CurrentLevelName;
	}
	else
	{
		CLog::Log("New Game");
		map = "/Game/Maps/Map";
	}


	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);

	UGameplayStatics::OpenLevel(GetWorld(), (FName)map);
}

void UCMainMenu::OpenOptionMenu()
{
	CLog::Print("OpenOptionMenu");
}
