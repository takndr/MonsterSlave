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
	void SettingSlot(FCItemStruct InItem);
	FORCEINLINE bool IsFilled() { return bFilled; }
protected:
	virtual bool Initialize() override;
	UFUNCTION(BlueprintCallable)
		void EquipItem();
private:
	void EquipBow();
	void EquipSword();


// ===========================================
private:
	class UCInventory* Inventory;
// ===========================================
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* SlotImage;

protected:
	UPROPERTY(BlueprintReadWrite)
		FCItemStruct InvenSlotItem;

	UPROPERTY(BlueprintReadOnly)
		bool bFilled = false;

private:
	
};
