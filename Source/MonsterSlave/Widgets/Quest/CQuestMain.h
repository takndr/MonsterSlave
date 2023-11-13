#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CQuestMain.generated.h"

UCLASS()
class MONSTERSLAVE_API UCQuestMain : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ============================================================================
private:
	void OffQuestWidget();
// ============================================================================
private:
	UFUNCTION()
		void OnClickedOkButton();

	UFUNCTION()
		void OnClickedCancelButton();

// ============================================================================
private:
	class ACharacter* OwnerCharacter;
// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* OkButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CancelButton;
};
