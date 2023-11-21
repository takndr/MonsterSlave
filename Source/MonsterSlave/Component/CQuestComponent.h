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
	FORCEINLINE TArray<class UCQuestData*> GetQuestDatas() { return QuestDatas; }
// ============================================================================
private:
	UFUNCTION()
		void SaveQuestDatas();
// ============================================================================
private:
	class ACharacter* OwnerCharacter;
// ============================================================================
protected:
	UPROPERTY(EditDefaultsOnly)
		TArray<class UCQuestData*> QuestDatas;
};
