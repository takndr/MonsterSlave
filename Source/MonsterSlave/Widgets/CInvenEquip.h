#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CInvenEquip.generated.h"

UCLASS()
class MONSTERSLAVE_API UCInvenEquip : public UUserWidget
{
	GENERATED_BODY()

public:


protected:
	virtual bool Initialize() override;


// =====================================================
public:
	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* EquipSlotSword;

	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* EquipSlotBow;

};
