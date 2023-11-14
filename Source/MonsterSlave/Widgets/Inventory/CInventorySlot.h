#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CInventorySlot.generated.h"

UCLASS()
class MONSTERSLAVE_API UCInventorySlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void SettingSlot(FCItemStruct InItem);
	FORCEINLINE bool IsFilled() { return bFilled; }
private:
	void EquipBow();
	void EquipSword();
// ============================================================================
protected:
	UFUNCTION(BlueprintCallable)
		void EquipItem();
// ============================================================================
private:
	class ACharacter* OwnerCharacter;
	class UCInventory* Inventory;
// ============================================================================
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
