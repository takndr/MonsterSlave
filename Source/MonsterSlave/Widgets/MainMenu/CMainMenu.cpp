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
	// save파일 가져와서 저장된 현재 레벨이 어디인지 알아내고
	// 해당 레벨로 이동
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
