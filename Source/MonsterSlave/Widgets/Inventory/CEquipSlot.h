#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CEquipSlot.generated.h"

UCLASS()
class MONSTERSLAVE_API UCEquipSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void SettingSlot(FCItemStruct InItem);
	FORCEINLINE bool IsEquipped() const { return bEquipped; }
	FORCEINLINE FCItemStruct GetItem() const { return EquipSlotItem; }

protected:
	virtual bool Initialize() override;

protected:
	UFUNCTION(BlueprintCallable)
		void UnEquipItem();

// ===================================================
public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		UTexture2D* DefaultImage;

protected:
	UPROPERTY(BlueprintReadOnly)
		FCItemStruct EquipSlotItem;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* SlotImage;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bEquipped = false;
};
