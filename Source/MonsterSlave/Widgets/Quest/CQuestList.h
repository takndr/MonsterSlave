#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CQuestList.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FClickedListSignature, class UCQuestData*, InQuestData);

UCLASS()
class MONSTERSLAVE_API UCQuestList : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ============================================================================
public:
	FORCEINLINE void SetQuestData(class UCQuestData* InQuestData) { QuestData = InQuestData; }
// ============================================================================
private:
	UFUNCTION()
		void OnClickedListButton();
// ============================================================================
public:
	FClickedListSignature OnClickedList;
private:
	class UCQuestData* QuestData;
// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* ListButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestName;
};
