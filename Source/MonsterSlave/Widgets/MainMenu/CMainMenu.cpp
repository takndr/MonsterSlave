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
	//CLog::Print("Connect");
	CLog::Print(UGameplayStatics::GetCurrentLevelName(GetWorld()));


	// �����Ҷ� �ش� �Լ��� ����
	UGameplayStatics::GetCurrentLevelName(GetWorld());


	// ����� ���� ������ ����
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	CheckNull(saveGame);

	//UGameplayStatics::OpenLevel(GetWorld(), saveGame->CurrentLevelName);
}

void UCMainMenu::OpenOptionMenu()
{
	CLog::Print("OpenOptionMenu");
}
