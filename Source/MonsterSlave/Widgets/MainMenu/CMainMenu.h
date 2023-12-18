#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainMenu.generated.h"

UCLASS()
class MONSTERSLAVE_API UCMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ==================================================================

// ==================================================================
private:
	UFUNCTION()
		void Connect();

	UFUNCTION()
		void OpenOptionMenu();
// ==================================================================

// ==================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UImage* OptionImage;

	UPROPERTY(meta = (BindWidget))
		class UBorder* MenuBorder;
};
