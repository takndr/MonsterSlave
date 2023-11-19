#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGiftSlot.generated.h"

UCLASS()
class MONSTERSLAVE_API UCGiftSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:	
	FORCEINLINE	void SetItemData(class UCItemData* InItemData) { ItemData = InItemData; }

private:
	class UCItemData* ItemData;

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* SlotImage;
};
