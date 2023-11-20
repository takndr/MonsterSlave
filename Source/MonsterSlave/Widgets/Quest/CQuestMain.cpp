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

	// 버튼 바인딩
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

	// 수락버튼을 누를경우 PlayerMainWidget에 퀘스트 관련쪽에다가 추가해주는 Delegate를 만들어서 바로 추가되고
	if(temp.QuestProgress == EQuestProgressType::Available)
	{
		// 플레이어에게 현재 퀘스트 전달
		ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		player->Quests.Add(SelectedQuest);

		// QuestComponent에서 QuestProgress를 InProgress로 변경
		SelectedQuest->SetProgressType(EQuestProgressType::InProgress);
	}

	// 완료버튼 누를 경우 PlayerMainWidget에서 바로 제거되어야함
	if (temp.QuestProgress == EQuestProgressType::Completed)
	{
		// 보상들 플레이어에게 Add
		ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		for (auto giftData : temp.GiftDatas)
		{
			player->AddItem(giftData);
		}

		// 퀘스트 디테일 widget에서 제거

		// QuestComponent에서의 QuestProgress를 Clear로 변경
		SelectedQuest->SetProgressType(EQuestProgressType::Clear);

		// 다음 연계될 퀘스트가 있으면 다음 퀘스트 QuestProgress를 Available로 변경
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

	// QuestList 위젯을 생성하여
	UCQuestList* quest = CreateWidget<UCQuestList>(GetWorld(), QuestListWidgetClass);
	quest->SetQuest(Quest);
	quest->OnClickedList.BindUFunction(this, "SetQuestDetails");

	// ScrollBox에 추가
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

	// 퀘스트 이름 등록
	Name->SetText(temp.QuestName);
	// 퀘스트 내용 등록
	Conversation->SetText(temp.QuestConversation);

	GiftList->ClearChildren();

	// 보상 칸 등록
	uint8 index = 0;
	for (auto giftData : temp.GiftDatas)
	{
		UCGiftSlot* gift = CreateWidget<UCGiftSlot>(GetWorld(), GiftSlotWidgetClass);
		gift->SetItemData(giftData);
		GiftList->AddChildToGrid(gift, 0, index);
		index++;
	}

	// 클릭 버튼 변경
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