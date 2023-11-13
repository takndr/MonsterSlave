#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemStruct.h"
#include "CQuestComponent.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Location, Battle
};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()
public:
	EQuestType QuestType;
	FString QuestName;
	FString QuestDetails;
	TArray<FCItemStruct> Gifts;
	FQuest* NextQuest;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCQuestComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCQuestComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
