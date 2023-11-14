#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CInventory.generated.h"

UCLASS()
class MONSTERSLAVE_API UCInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE bool IsOpened() { return Opened; }

	void Attach();
	void Detach();
	uint32 AddItem(FCItemStruct item);

protected:
	virtual void NativeConstruct() override;
private:
	void Update();

// ============================================================================
private:
	class ACharacter* OwnerCharacter;
// ============================================================================

public:
	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* SwordEquipment;

	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* BowEquipment;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* BagPannel;

protected:

private:
	bool Opened = false;
	uint32 MaxInventory = 30;
};
// 한 줄에 몇개의 아이템이..? = 5개