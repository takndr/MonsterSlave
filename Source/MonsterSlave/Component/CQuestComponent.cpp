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

	// 포탈에 저장 관련 델리게이트 바인딩
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPortal::StaticClass(), outActors);
	for (auto outActor : outActors)
	{
		ACPortal* outPortal = Cast<ACPortal>(outActor);
		if (outPortal == nullptr) continue;

		outPortal->OnPortalSave.AddDynamic(this, &UCQuestComponent::SaveQuestDatas);
	}
}

void UCQuestComponent::SaveQuestDatas()
{
	for (auto questData : QuestDatas)
	{
		questData->SaveData();
	}
}
