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
	SlotImage->SetBrushFromTexture(InItem.Picture);
	SlotImage->SetBrushSize(FVector2D(32.0f));
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	InvenItem = InItem;
	bFilled = true;
}

void UCInventorySlot::EquipItem() {
	CLog::Log("Equiped Item!!");

	// �Ŀ� ���â�� �������� ä���������� ��ü�ϴ� ���·� ����
	switch (InvenItem.WeaponType) {
		case EWeaponType::Sword: {
			EquipSword();
			break;
		}
		case EWeaponType::Bow: {
			EquipBow();
			break;
		}
	}

	bFilled = false;
}

void UCInventorySlot::EquipSword() {
	CLog::Log("Equip Sword!");
	
	// �����  EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���

	// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	playertest->InventoryWidget->Equipment->Sword->SettingSlot(InvenItem);

	// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
	playertest->RemoveItem(InvenItem);

	// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
	
}

void UCInventorySlot::EquipBow() {
	CLog::Log("Equip Bow!");

	// �����  EquipSlot�� ����ִ� �����ϰ� ����������, ���� EquipSlot�� �������� ��������, ��ü�� �����ؾ���

	// EquipSlot�� ��� Ȥ�� EquipSlot�� �������� ��ϵǾ� ���� ��� ��ü
	ACPlayer* playertest = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	playertest->InventoryWidget->Equipment->Bow->SettingSlot(InvenItem);

	// Player�� Item�迭���� �ش� ������ ���� Ȥ�� ��ü�� �������� ���� ��� �����ۿ� �߰�
	playertest->RemoveItem(InvenItem);

	// �κ��丮 â���� �ش� ������ ���� �� ��ü�� �������� ������� �κ��丮�� �߰�
	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f));
}

