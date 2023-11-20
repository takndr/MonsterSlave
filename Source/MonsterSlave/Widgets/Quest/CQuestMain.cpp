#include "Widgets/Quest/CQuestMain.h"

#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"

#include "Widgets/Quest/CQuestList.h"
#include "Widgets/Quest/CGiftSlot.h"
#include "Player/CPlayer.h"
#include "Items/CItemData.h"

#include "Global.h"

UCQuestMain::UCQuestMain(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CHelpers::GetClass(&QuestListWidgetClass, "/Game/Widgets/Widget/Quest/WB_QuestList");
	CHelpers::GetClass(&GiftSlotWidgetClass, "/Game/Widgets/Widget/Quest/WB_GiftSlot");
}

void UCQuestMain::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
	OkButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedOkButton);
	CancelButton->OnClicked.AddDynamic(this, &UCQuestMain::OnClickedCancelButton);
}

void UCQuestMain::NativeDestruct()
{
	Super::NativeDestruct();

	OkButton->OnClicked.Clear();
	CancelButton->OnClicked.Clear();
}

void UCQuestMain::OnClickedOkButton()
{
	FMyQuest temp = SelectedQuest->GetQuestInfo();

	// ������ư�� ������� PlayerMainWidget�� ����Ʈ �����ʿ��ٰ� �߰����ִ� Delegate�� ���� �ٷ� �߰��ǰ�
	if(temp.QuestProgress == EQuestProgressType::Available)
	{
		// �÷��̾�� ���� ����Ʈ ����
		ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		player->Quests.Add(SelectedQuest);

		// QuestComponent���� QuestProgress�� InProgress�� ����
		SelectedQuest->SetProgressType(EQuestProgressType::InProgress);
	}

	// �Ϸ��ư ���� ��� PlayerMainWidget���� �ٷ� ���ŵǾ����
	if (temp.QuestProgress == EQuestProgressType::Completed)
	{
		// ����� �÷��̾�� Add
		ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		for (auto giftData : temp.GiftDatas)
		{
			player->AddItem(giftData);
		}

		// ����Ʈ ������ widget���� ����

		// QuestComponent������ QuestProgress�� Clear�� ����
		SelectedQuest->SetProgressType(EQuestProgressType::Clear);

		// ���� ����� ����Ʈ�� ������ ���� ����Ʈ QuestProgress�� Available�� ����
	}



	OffQuestWidget();
}

void UCQuestMain::OnClickedCancelButton()
{
	OffQuestWidget();
}

void UCQuestMain::AddQuestList(class ACQuest* Quest)
{
	CheckFalse(((Quest->GetQuestInfo().QuestProgress == EQuestProgressType::Available) || (Quest->GetQuestInfo().QuestProgress == EQuestProgressType::InProgress) || (Quest->GetQuestInfo().QuestProgress == EQuestProgressType::Completed)));

	// QuestList ������ �����Ͽ�
	UCQuestList* quest = CreateWidget<UCQuestList>(GetWorld(), QuestListWidgetClass);
	quest->SetQuest(Quest);
	quest->OnClickedList.BindUFunction(this, "SetQuestDetails");

	// ScrollBox�� �߰�
	QuestList->AddChild(quest);
}

void UCQuestMain::OffQuestWidget()
{
	Clear();

	SetVisibility(ESlateVisibility::Collapsed);

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);

	this->RemoveFromParent();
}

void UCQuestMain::Clear()
{
	GiftList->ClearChildren();
	QuestList->ClearChildren();
	SelectedQuest = nullptr;
	Name->SetText(FText::FromString(""));
	Conversation->SetText(FText::FromString(""));
	ConfirmText->SetText(FText::FromString("OK"));
}

void UCQuestMain::SetQuestDetails(ACQuest* InQuest)
{
	SelectedQuest = InQuest;
	FMyQuest temp = SelectedQuest->GetQuestInfo();

	// ����Ʈ �̸� ���
	Name->SetText(temp.QuestName);
	// ����Ʈ ���� ���
	Conversation->SetText(temp.QuestConversation);

	GiftList->ClearChildren();

	// ���� ĭ ���
	uint8 index = 0;
	for (auto giftData : temp.GiftDatas)
	{
		UCGiftSlot* gift = CreateWidget<UCGiftSlot>(GetWorld(), GiftSlotWidgetClass);
		gift->SetItemData(giftData);
		GiftList->AddChildToGrid(gift, 0, index);
		index++;
	}

	// Ŭ�� ��ư ����
	if (temp.QuestProgress == EQuestProgressType::Available)
	{
		ConfirmText->SetText(FText::FromString("Accept"));
	}
	if (temp.QuestProgress == EQuestProgressType::InProgress)
	{
		ConfirmText->SetText(FText::FromString("Progressed"));
	}
	if (temp.QuestProgress == EQuestProgressType::Completed)
	{
		ConfirmText->SetText(FText::FromString("Complete"));
	}
}