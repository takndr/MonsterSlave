#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemStruct.h"
#include "CQuest.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Min, Move, Battle, Collect, Conversation, Max
};

UENUM(BlueprintType)
enum class EQuestProgressType : uint8
{
	Min, UnAvailable, Available, InProgress, Completed, Clear, Max
};

USTRUCT(Atomic, BlueprintType)
struct FMyQuest
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
		TArray<class UCItemData*> GiftDatas;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ACQuest* NextQuest;
};

UCLASS()
class MONSTERSLAVE_API ACQuest : public AActor
{
	GENERATED_BODY()
public:	
	ACQuest();
protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE FMyQuest GetQuestInfo() { return QuestInfo; }
	FORCEINLINE void SetProgressType(EQuestProgressType InType) { QuestInfo.QuestProgress = InType; }
protected:
	UPROPERTY(EditAnywhere, Category = "Description")
		FMyQuest QuestInfo;
};
