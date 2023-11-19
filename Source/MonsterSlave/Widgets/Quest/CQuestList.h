#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest/CQuest.h"
#include "CQuestList.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FClickedListSignature, class ACQuest*, InQuest);

UCLASS()
class MONSTERSLAVE_API UCQuestList : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ============================================================================
public:
	FORCEINLINE void SetQuest(ACQuest* InQuest) { Quest = InQuest; }
// ============================================================================
private:
	UFUNCTION()
		void OnClickedListButton();
// ============================================================================
public:
	FClickedListSignature OnClickedList;

private:
	ACQuest* Quest;
// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* ListButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestName;
};
