#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerQuestLog.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerQuestLog : public UUserWidget
{
	GENERATED_BODY()
public:
	UCPlayerQuestLog(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
// ============================================================================
public:
	bool IsOpened() { return bOpened; }
	void Attach();
	void Detach();
	void AddQuestList(class UCQuestData* InQuest);
// ============================================================================
public:

private:
	UFUNCTION()
		void SetQuestDetails(class UCQuestData* InQuest);
// ============================================================================
private:
	class ACharacter* OwnerCharacter;
	bool bOpened = false;

	TSubclassOf<class UCQuestList> QuestListWidgetClass;
	TSubclassOf<class UCGiftSlot> GiftSlotWidgetClass;
// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UOverlay* List;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ProgressBox;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* ClearBox;

	UPROPERTY(meta = (BindWidget))
		class USizeBox* ClearCaseBox;

	UPROPERTY(meta = (BindWidget))
		class USizeBox* ObjectBox;

	UPROPERTY(meta = (BindWidget))
		class UOverlay* Detail;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestDetails;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestObject;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* QuestConversation;

	UPROPERTY(meta = (BindWidget))
		class UGridPanel* GiftList;
};