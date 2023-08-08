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
	void AddItem(FCItemStruct item);			// 아이템 먹었을 때, 가방에 추가해주는 함수 | 매개변수로 item struct 추가 예정

protected:
	virtual bool Initialize() override;

private:
	void Update();								// 초기 인벤토리 가방 업데이트
	void SetRowColumn();						// 그리드패널에 아이템 추가하고 나서 다음 추가할 행,열 계산

// =====================================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* BagPannel;

	TSubclassOf<class UCInventorySlot> Slot;

	bool Opened = false;
	int32 MaxInColumn = 5;
	int32 CurrentColumn = 0;
	int32 CurrentRow = 0;
};
// 한 줄에 몇개의 아이템이..? = 5개