#include "Component/CActionComponent.h"

#include "Component/CStateComponent.h"

#include "Global.h"

UCActionComponent::UCActionComponent()
{
	// ...
}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCActionComponent::Action() {
	// WeaponComponent�� GetCurrentWeapon�� GetCurrentWeaponType�� �̿��Ͽ�
	// ������ �����͹迭���� �ش� Ÿ�Կ� �´� ��Ÿ�ֵ��� ����
	// GetCurrentWeapon�� ���Ͽ� ������ EquipItem�� Action�� �����Ͽ� ���� ���ο����� ��Ÿ�ָ� �����ų ���� �ִٸ� ����
}