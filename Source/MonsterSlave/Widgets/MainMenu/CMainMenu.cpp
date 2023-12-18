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
	//CLog::Print("Connect");
	CLog::Print(UGameplayStatics::GetCurrentLevelName(GetWorld()));


	// 저장할땐 해당 함수로 저장
	UGameplayStatics::GetCurrentLevelName(GetWorld());


	// 저장된 정보 있으면 저장
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	CheckNull(saveGame);

	//UGameplayStatics::OpenLevel(GetWorld(), saveGame->CurrentLevelName);
}

void UCMainMenu::OpenOptionMenu()
{
	CLog::Print("OpenOptionMenu");
}
