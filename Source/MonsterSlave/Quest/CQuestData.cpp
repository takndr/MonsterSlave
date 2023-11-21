#include "Quest/CQuestData.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

#include "Global.h"

void UCQuestData::BeginPlay()
{
	switch (Quest.QuestType)
	{
		case EQuestType::Move:
			OnQuestCheck.BindUFunction(this, "MoveToLocation");
			break;
		case EQuestType::Killed:
			OnQuestCheck.BindUFunction(this, "KilledEnemy");
			break;
		case EQuestType::Collect:
			OnQuestCheck.BindUFunction(this, "CollectedItems");
			break;
		case EQuestType::Conversation:
			OnQuestCheck.BindUFunction(this, "ConversationToNpc");
			break;
	}
}

void UCQuestData::SetProgressType(EQuestProgressType InType)
{
	Quest.QuestProgress = InType;
}

void UCQuestData::ClearQuest()
{
	if (OnQuestCheck.IsBound() == true)
	{
		OnQuestCheck.Clear();
	}

	CheckNull(Quest.NextQuest);
	Quest.NextQuest->Quest.QuestProgress = EQuestProgressType::Available;
}

void UCQuestData::MoveToLocation(AActor* InActor)
{
	CheckFalse(Quest.QuestObjectives == InActor->GetClass());

	Quest.QuestProgress = EQuestProgressType::Completed;
	// Update UI
}

void UCQuestData::KilledEnemy(AActor* InActor)
{
	CheckFalse(Quest.QuestObjectives == InActor->GetClass());
	CurrentCount++;
	CurrentCount = FMath::Clamp(CurrentCount, (uint8)0, Quest.QuestNums);

	if (CurrentCount == Quest.QuestNums)
	{
		Quest.QuestProgress = EQuestProgressType::Completed;
		// Update UI
	}
}

void UCQuestData::CollectedItems(AActor* InActor)
{
	CheckFalse(Quest.QuestObjectives == InActor->GetClass());
	CurrentCount++;
	CurrentCount = FMath::Clamp(CurrentCount, (uint8)0, Quest.QuestNums);

	if (CurrentCount == Quest.QuestNums)
	{
		Quest.QuestProgress = EQuestProgressType::Completed;
		// Update UI
	}
}

void UCQuestData::ConversationToNpc(AActor* InActor)
{
	CheckFalse(Quest.QuestObjectives == InActor->GetClass());

	Quest.QuestProgress = EQuestProgressType::Completed;
	// Update UI
}