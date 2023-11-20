#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CEquipSlot.generated.h"

UCLASS()
class MONSTERSLAVE_API UCEquipSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void SettingSlot(class UCItemData* InItem);
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE class UCItemData* GetItem() { return Item; }
// ============================================================================
protected:
	UFUNCTION(BlueprintCallable)
		void UnEquipItem();
// ============================================================================
private:
	class ACharacter* OwnerCharacter;
// ============================================================================
public:
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
		UTexture2D* DefaultImage;

protected:
	UPROPERTY(BlueprintReadOnly)
		class UCItemData* Item;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* SlotButton;

	UPROPERTY(meta = (BindWidget))
		class UImage* SlotImage;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bEquipped = false;
};
