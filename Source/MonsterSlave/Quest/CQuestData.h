#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CQuestData.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Min, Move, Killed, Collect, Conversation, Max
};

UENUM(BlueprintType)
enum class EQuestProgressType : uint8
{
	Min, UnAvailable, Available, InProgress, Completed, Clear, Max
};

USTRUCT(Atomic, BlueprintType)
struct FQuest
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EQuestType QuestType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EQuestProgressType QuestProgress;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestConversation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestDetails;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> QuestObjectives;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		uint8 QuestNums;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UCItemData*> GiftDatas;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCQuestData* NextQuest;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FQuestCheckSignature, class AActor*, InActor);

UCLASS()
class MONSTERSLAVE_API UCQuestData : public UDataAsset
{
	GENERATED_BODY()
public:
	void BeginPlay();
	void SetProgressType(EQuestProgressType InType);
	void ClearQuest();
private:
	UFUNCTION()
		void MoveToLocation(class AActor* InActor);

	UFUNCTION()
		void KilledEnemy(class AActor* InActor);

	UFUNCTION()
		void CollectedItems(class AActor* InActor);

	UFUNCTION()
		void ConversationToNpc(class AActor* InActor);
public:
	FQuestCheckSignature OnQuestCheck;
	uint8 CurrentCount = 0;
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Quests")
		FQuest Quest;
};
