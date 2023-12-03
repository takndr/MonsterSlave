#include "Quest/CQuestData.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

#include "GameMode/CSaveGame.h"

#include "Global.h"

void UCQuestData::BeginPlay()
{
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));

	if (saveGame != nullptr)
	{
		if (saveGame->AllQuests.Num() != 0)
		{
			for (auto quest : saveGame->AllQuests)
			{
				if (Quest.QuestID == quest.QuestID)
				{
					Quest = quest;
					break;
				}
			}
		}
	}

	CheckTrue(Quest.QuestProgress == EQuestProgressType::Clear);
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
	if (OnQuestCheck.IsBound())
	{
		OnQuestCheck.Clear();
	}

	CheckNull(Quest.NextQuest);
	Quest.NextQuest->Quest.QuestProgress = EQuestProgressType::Available;
}

void UCQuestData::SaveData()
{
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	if (Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0)) != nullptr)
	{
		saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	}
	
	int index = saveGame->AllQuests.Find(Quest);

	if (index == INDEX_NONE)
	{
		saveGame->AllQuests.AddUnique(Quest);
	}
	else
	{
		saveGame->AllQuests[index] = Quest;
	}

	UGameplayStatics::SaveGameToSlot(saveGame, "Test", 0);
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
	Quest.CurrentCount++;
	Quest.CurrentCount = FMath::Clamp(Quest.CurrentCount, (uint8)0, Quest.QuestNums);

	if (Quest.CurrentCount == Quest.QuestNums)
	{
		Quest.QuestProgress = EQuestProgressType::Completed;
		// Update UI
	}
}

void UCQuestData::CollectedItems(AActor* InActor)
{
	CheckFalse(Quest.QuestObjectives == InActor->GetClass());
	Quest.CurrentCount++;
	Quest.CurrentCount = FMath::Clamp(Quest.CurrentCount, (uint8)0, Quest.QuestNums);

	if (Quest.CurrentCount == Quest.QuestNums)
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