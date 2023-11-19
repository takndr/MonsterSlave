#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest/CQuest.h"
#include "CQuestMain.generated.h"

DECLARE_DYNAMIC_DELEGATE(FQuestAcceptSignature);
DECLARE_DYNAMIC_DELEGATE(FQuestClearSignature);

UCLASS()
class MONSTERSLAVE_API UCQuestMain : public UUserWidget
{
	GENERATED_BODY()
public:
	UCQuestMain(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
// ============================================================================
public:
	void AddQuestList(class ACQuest* Quest);

private:
	void OffQuestWidget();
	//void Clear();
// ============================================================================
private:
	UFUNCTION()
		void OnClickedOkButton();

	UFUNCTION()
		void OnClickedCancelButton();

	UFUNCTION()
		void SetQuestDetails(ACQuest* InQuest);

// ============================================================================
public:
	FQuestAcceptSignature OnQuestAccept;
	FQuestClearSignature OnQuestClear;

private:
	class ACharacter* OwnerCharacter;
	TSubclassOf<class UCQuestList> QuestListWidgetClass;
	TSubclassOf<class UCGiftSlot> GiftSlotWidgetClass;
	ACQuest* SelectedQuest;

// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* QuestList;

	UPROPERTY(meta = (BindWidget))
		class UButton* OkButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
		class UGridPanel* GiftList;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Conversation;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ConfirmText;
};
