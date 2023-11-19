#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CQuestComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCQuestComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCQuestComponent();
protected:
	virtual void BeginPlay() override;
// ============================================================================
public:
	FORCEINLINE TArray<class ACQuest*> GetQuests() { return Quests; }
	void DeleteQuest(class ACQuest* InQuest);
// ============================================================================
private:
	class ACharacter* OwnerCharacter;
	TArray<class ACQuest*> Quests;
// ============================================================================
protected:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ACQuest>> QuestClasses;

};
