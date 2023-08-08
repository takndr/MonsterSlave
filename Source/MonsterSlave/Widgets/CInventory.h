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
	void AddItem(FCItemStruct item);			// ������ �Ծ��� ��, ���濡 �߰����ִ� �Լ� | �Ű������� item struct �߰� ����

protected:
	virtual bool Initialize() override;

private:
	void Update();								// �ʱ� �κ��丮 ���� ������Ʈ
	void SetRowColumn();						// �׸����гο� ������ �߰��ϰ� ���� ���� �߰��� ��,�� ���

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
// �� �ٿ� ��� ��������..? = 5��