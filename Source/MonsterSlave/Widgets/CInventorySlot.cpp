#include "CInventorySlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Widgets/CInventory.h"
#include "Widgets/CInvenEquip.h"
#include "Widgets/CEquipSlot.h"
#include "Player/CPlayer.h"

#include "Global.h"

bool UCInventorySlot::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInventorySlot::SettingSlot(FCItemStruct InItem) {
	InvenSlotItem = InItem;
	bFilled = true;

	SlotImage->SetBrushFromTexture(InvenSlotItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
}

void UCInventorySlot::EquipItem() {
	CLog::Log("Equiped Item!!");

	// �Ŀ� ���â�� �������� ä���������� ��ü�ϴ� ���·� ����
	switch (InvenSlotItem.WeaponType) {
		case EWeaponType::Sword: {
			EquipSword();
			break;
		}
		case EWeaponType::Bow: {
			EquipBow();
			break;
		}
	}

	
}

void UCInventorySlot::EquipSword() {
	CLog::Log("Equip Sword!");
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// ����� EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
	if (playertest->InventoryWidget->Equipment->EquipSlotSword->IsEquipped() == true) {
		FCItemStruct temp = playertest->InventoryWidget->Equipment->EquipSlotSword->GetItem();
		playertest->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		playertest->EquipSword(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
		playertest->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
		playertest->RemoveItem(InvenSlotItem);
		// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// �÷��̾�� ������ ������ ����
		playertest->EquipSword(InvenSlotItem);
		bFilled = false;
	}

	
	
}

void UCInventorySlot::EquipBow() {
	CLog::Log("Equip Bow!");
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// �����  EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
	if (playertest->InventoryWidget->Equipment->EquipSlotBow->IsEquipped() == true) {
		FCItemStruct temp = playertest->InventoryWidget->Equipment->EquipSlotBow->GetItem();
		playertest->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		playertest->EquipBow(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
		playertest->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
		playertest->RemoveItem(InvenSlotItem);
		// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// �÷��̾�� ������ ������ ����
		playertest->EquipBow(InvenSlotItem);
		bFilled = false;
	}
}

