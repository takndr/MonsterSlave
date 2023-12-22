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

	if (saveGame != nullptr)
	{
		FString map = "/Game/Maps/" + saveGame->CurrentLevelName;
		UGameplayStatics::OpenLevel(GetWorld(), (FName)map);
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/Map");
	}
}

void UCMainMenu::OpenOptionMenu()
{
	CLog::Print("OpenOptionMenu");
}
