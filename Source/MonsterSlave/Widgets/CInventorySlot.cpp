#include "CInventorySlot.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Widgets/CInventory.h"
#include "Widgets/CInvenEquip.h"
#include "Widgets/CEquipSlot.h"
#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"

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
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);

	// ����� EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
	if (player->InventoryWidget->Equipment->EquipSlotSword->IsEquipped() == true) {
		FCItemStruct temp = player->InventoryWidget->Equipment->EquipSlotSword->GetItem();
		player->ReplaceInventoryItem(InvenSlotItem, temp);
		player->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		
		weapon->SetSword(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
		player->InventoryWidget->Equipment->EquipSlotSword->SettingSlot(InvenSlotItem);
		// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
		player->RemoveInventoryItem(InvenSlotItem);
		// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// �÷��̾�� ������ ������ ����
		weapon->SetSword(InvenSlotItem);
		bFilled = false;
	}	
}

void UCInventorySlot::EquipBow() {
	CLog::Log("Equip Bow!");
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(player);

	// �����  EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���
	if (player->InventoryWidget->Equipment->EquipSlotBow->IsEquipped() == true) {
		FCItemStruct temp = player->InventoryWidget->Equipment->EquipSlotBow->GetItem();
		player->ReplaceInventoryItem(InvenSlotItem, temp);
		player->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		weapon->SetBow(InvenSlotItem);
		SettingSlot(temp);
	}
	else {
		// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
		player->InventoryWidget->Equipment->EquipSlotBow->SettingSlot(InvenSlotItem);
		// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
		player->RemoveInventoryItem(InvenSlotItem);
		// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
		// �÷��̾�� ������ ������ ����
		weapon->SetBow(InvenSlotItem);
		bFilled = false;
	}
}

