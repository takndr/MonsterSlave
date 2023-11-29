#include "Component/CQuestComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

#include "Quest/CQuestData.h"
#include "etc/CPortal.h"

#include "Global.h"

UCQuestComponent::UCQuestComponent()
{
}

void UCQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	for (auto questData : QuestDatas)
	{
		questData->BeginPlay();
	}

	// ��Ż�� ���� ���� ��������Ʈ ���ε�
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPortal::StaticClass(), outActors);
	for (auto outActor : outActors)
	{
		ACPortal* outPortal = Cast<ACPortal>(outActor);
		if (outPortal == nullptr) continue;

		outPortal->OnPortalSave.AddDynamic(this, &UCQuestComponent::SaveQuestDatas);
	}
}

bool UCQuestComponent::HasAvailableQuest()
{
	bool result = false;

	for (auto questData : QuestDatas)
	{
		result = result || (questData->Quest.QuestProgress == EQuestProgressType::Available);
	}

	return result;
}

bool UCQuestComponent::HasCompletedQuest()
{
	bool result = false;

	for (auto questData : QuestDatas)
	{
		result = result || (questData->Quest.QuestProgress == EQuestProgressType::Completed);
	}

	return result;
}

void UCQuestComponent::SaveQuestDatas()
{
	for (auto questData : QuestDatas)
	{
		questData->SaveData();
	}
}
