#include "Quest/CQuest.h"

#include "Global.h"

ACQuest::ACQuest()
{

}

void ACQuest::BeginPlay()
{
	Super::BeginPlay();
	
	switch (QuestInfo.QuestType)
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

void ACQuest::MoveToLocation(AActor* InActor)
{
	CheckFalse(QuestInfo.QuestObjectives == InActor->GetClass());

	SetProgressType(EQuestProgressType::Completed);
	// Update UI
}

void ACQuest::KilledEnemy(AActor* InActor)
{
	CLog::Print("Check1");
	CheckFalse(QuestInfo.QuestObjectives == InActor->GetClass());
	CLog::Print("Check2");
	CurrentCount++;
	CurrentCount = FMath::Clamp(CurrentCount, (uint8)0, QuestInfo.QuestNums);

	if (CurrentCount == QuestInfo.QuestNums)
	{
		SetProgressType(EQuestProgressType::Completed);
		// Update UI
	}
}

void ACQuest::CollectedItems(AActor* InActor)
{
	CheckFalse(QuestInfo.QuestObjectives == InActor->GetClass());
	CurrentCount++;
	CurrentCount = FMath::Clamp(CurrentCount, (uint8)0, QuestInfo.QuestNums);

	if (CurrentCount == QuestInfo.QuestNums)
	{
		SetProgressType(EQuestProgressType::Completed);
		// Update UI
	}
}

void ACQuest::ConversationToNpc(AActor* InActor)
{
	CheckFalse(QuestInfo.QuestObjectives == InActor->GetClass());

	SetProgressType(EQuestProgressType::Completed);
	// Update UI
}


