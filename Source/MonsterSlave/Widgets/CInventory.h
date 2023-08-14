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
	UCInventory(const FObjectInitializer& ObjectInitializer);
	FORCEINLINE bool IsOpened() { return Opened; }

	void Attach();
	void Detach();
	uint32 AddItem(FCItemStruct item);			// 아이템 먹었을 때, 가방에 추가해주는 함수 | 매개변수로 item struct 추가 예정

protected:
	virtual bool Initialize() override;

private:
	void Update();								// 초기 인벤토리 가방 업데이트

// =====================================

public:
	UPROPERTY(meta = (BindWidget))
		class UCInvenEquip* Equipment;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* BagPannel;

protected:

private:
	bool Opened = false;
	uint32 MaxInventory = 15;
};
// 한 줄에 몇개의 아이템이..? = 5개