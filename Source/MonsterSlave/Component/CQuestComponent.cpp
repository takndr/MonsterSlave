#include "Component/CQuestComponent.h"

#include "GameFramework/Character.h"

#include "Quest/CQuest.h"

#include "Global.h"

UCQuestComponent::UCQuestComponent()
{
}

void UCQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());


	for (auto QuestClass : QuestClasses)
	{
		ACQuest* temp;
		FTransform transform = OwnerCharacter->GetActorTransform();
		temp = GetWorld()->SpawnActorDeferred<ACQuest>(QuestClass, transform, OwnerCharacter);
		temp->FinishSpawning(transform);
		temp->AttachToActor(OwnerCharacter, FAttachmentTransformRules::KeepRelativeTransform);
		Quests.Add(temp);
	}
}

void UCQuestComponent::DeleteQuest(class ACQuest* InQuest)
{

}


