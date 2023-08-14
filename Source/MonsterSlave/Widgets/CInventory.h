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
	uint32 AddItem(FCItemStruct item);			// ������ �Ծ��� ��, ���濡 �߰����ִ� �Լ� | �Ű������� item struct �߰� ����

protected:
	virtual bool Initialize() override;

private:
	void Update();								// �ʱ� �κ��丮 ���� ������Ʈ

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
// �� �ٿ� ��� ��������..? = 5��