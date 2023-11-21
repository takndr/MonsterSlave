#include "Component/CQuestComponent.h"

#include "GameFramework/Character.h"

#include "Quest/CQuestData.h"

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
}

