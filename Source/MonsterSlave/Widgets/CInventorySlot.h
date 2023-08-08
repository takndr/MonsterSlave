#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CInventorySlot.generated.h"

UCLASS()
class MONSTERSLAVE_API UCInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SettingSlot(FCItemStruct item);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void Clicked();

	UFUNCTION()
		void Hovered();

	UFUNCTION()
		void UnHovered();

// ===========================================

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SlotButton;

private:
	UPROPERTY(meta = (BindWidget))
		class UUserWidget* Description;
};
