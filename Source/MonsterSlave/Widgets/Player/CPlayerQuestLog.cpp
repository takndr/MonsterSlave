#include "Widgets/Player/CPlayerQuestLog.h"

#include "Components/ScrollBox.h"
#include "Components/Overlay.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

#include "Quest/CQuestData.h"
#include "Items/CItemData.h"
#include "Widgets/Quest/CQuestList.h"
#include "Widgets/Quest/CGiftSlot.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"
#include "Player/CPlayer.h"

#include "Global.h"

UCPlayerQuestLog::UCPlayerQuestLog(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CHelpers::GetClass(&QuestListWidgetClass, "/Game/Widgets/Widget/Quest/WB_QuestList");
	CHelpers::GetClass(&GiftSlotWidgetClass, "/Game/Widgets/Widget/Quest/WB_GiftSlot");
}

void UCPlayerQuestLog::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);

	// 플레이어가 가지고 있는 Quests를 확인하여 Progress이면 진행중쪽에, Clear이면 완료 쪽으로
	TArray<UCQuestData*> quests = player->Quests;
	for (UCQuestData* quest : quests)
	{
		AddQuestList(quest);
	}
}

void UCPlayerQuestLog::NativeDestruct()
{
	Super::NativeDestruct();

	Detail->SetVisibility(ESlateVisibility::Hidden);

	ProgressBox->ClearChildren();
	ClearBox->ClearChildren();
	GiftList->ClearChildren();
}


void UCPlayerQuestLog::Attach()
{
	this->AddToViewport();

	bOpened = true;
	SetVisibility(ESlateVisibility::Visible);

	FInputModeGameAndUI inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);
}

void UCPlayerQuestLog::Detach()
{
	bOpened = false;
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

void UCPlayerQuestLog::AddQuestList(UCQuestData* InQuest)
{
	CheckNull(InQuest);
	CheckFalse(((InQuest->Quest.QuestProgress == EQuestProgressType::InProgress) || (InQuest->Quest.QuestProgress == EQuestProgressType::Clear) || (InQuest->Quest.QuestProgress == EQuestProgressType::Completed)));

	// QuestList 위젯을 생성하여
	UCQuestList* quest = CreateWidget<UCQuestList>(GetWorld(), QuestListWidgetClass);
	quest->SetQuestData(InQuest);
	quest->OnClickedList.BindUFunction(this, "SetQuestDetails");

	// ScrollBox에 추가
	if ((InQuest->Quest.QuestProgress == EQuestProgressType::InProgress) || (InQuest->Quest.QuestProgress == EQuestProgressType::Completed))
	{
		ProgressBox->AddChild(quest);
		return;
	}
	ClearBox->AddChild(quest);
}

void UCPlayerQuestLog::SetQuestDetails(UCQuestData* InQuest)
{
	Detail->SetVisibility(ESlateVisibility::Visible);

	QuestName->SetText(InQuest->Quest.QuestName);
	QuestDetails->SetText(InQuest->Quest.QuestDetails);
	QuestConversation->SetText(InQuest->Quest.QuestConversation);

	if ((InQuest->Quest.QuestType == EQuestType::Move) || (InQuest->Quest.QuestType == EQuestType::Conversation))
	{
		ClearCaseBox->SetVisibility(ESlateVisibility::Hidden);
		ObjectBox->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ClearCaseBox->SetVisibility(ESlateVisibility::Visible);
		ObjectBox->SetVisibility(ESlateVisibility::Visible);
	}

	// QuestObject 변경
	FString temp;
	if (InQuest->Quest.QuestType == EQuestType::Killed)
	{
		UObject* object = InQuest->Quest.QuestObjectives->GetDefaultObject();
		if (Cast<ACBoss>(object) != nullptr)
		{
			temp += Cast<ACBoss>(object)->GetBossName().ToString();
			temp += " : ";
			temp += FString::FromInt(InQuest->Quest.CurrentCount);
			temp += " / ";
			temp += FString::FromInt(InQuest->Quest.QuestNums);
		}
		if (Cast<ACDummyEnemy>(object) != nullptr)
		{
			temp += Cast<ACDummyEnemy>(object)->GetEnemyName().ToString();
			temp += " : ";
			temp += FString::FromInt(InQuest->Quest.CurrentCount);
			temp += " / ";
			temp += FString::FromInt(InQuest->Quest.QuestNums);
		}

	}
	if (InQuest->Quest.QuestType == EQuestType::Collect)
	{
		UObject* object = InQuest->Quest.QuestObjectives->GetDefaultObject();
		if (Cast<UCItemData>(object) != nullptr)
		{
			temp += Cast<UCItemData>(object)->Item.Name;
			temp += " : ";
			temp += FString::FromInt(InQuest->Quest.CurrentCount);
			temp += " / ";
			temp += FString::FromInt(InQuest->Quest.QuestNums);
		}
	}
	QuestObject->SetText(FText::FromString(temp));


	GiftList->ClearChildren();
	// 보상 칸 등록
	uint8 index = 0;
	for (auto giftData : InQuest->Quest.GiftDatas)
	{
		UCGiftSlot* gift = CreateWidget<UCGiftSlot>(GetWorld(), GiftSlotWidgetClass);
		gift->SetItemData(giftData);
		GiftList->AddChildToGrid(gift, 0, index);
		index++;
	}
}
