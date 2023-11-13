#include "Widgets/Quest/CQuestMain.h"

#include "Components/Button.h"

#include "Global.h"

void UCQuestMain::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
	OkButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedOkButton);
	CancelButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedCancelButton);
}

void UCQuestMain::OnClickedOkButton()
{
	// 내용 추가

	OffQuestWidget();
}

void UCQuestMain::OnClickedCancelButton()
{
	OffQuestWidget();
}

void UCQuestMain::OffQuestWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);
}