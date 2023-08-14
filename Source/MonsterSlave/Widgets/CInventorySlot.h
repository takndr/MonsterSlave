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
	__forceinline bool IsFilled() { return bFilled; }

protected:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
		void EquipItem();

private:
	void EquipBow();
	void EquipSword();


// ===========================================

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* SlotImage;

protected:
	UPROPERTY(BlueprintReadWrite)
		FCItemStruct InvenItem;

	UPROPERTY(BlueprintReadOnly)
		bool bFilled = false;

private:
	
};
