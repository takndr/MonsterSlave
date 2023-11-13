#include "Widgets/Quest/CQuestMain.h"

#include "Components/Button.h"

#include "Global.h"

void UCQuestMain::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
	OkButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedOkButton);
	CancelButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedCancelButton);
}

void UCQuestMain::OnClickedOkButton()
{
	// ���� �߰�

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