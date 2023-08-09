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

// ===========================================

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SlotButton;

protected:
	UPROPERTY(BlueprintReadWrite)
		FCItemStruct InvenItem;
};
