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
	// WeaponComponent의 GetCurrentWeapon과 GetCurrentWeaponType을 이용하여
	// 내부의 데이터배열에서 해당 타입에 맞는 몽타주들을 실행
	// GetCurrentWeapon을 통하여 가져온 EquipItem도 Action을 실행하여 만약 내부에서도 몽타주를 실행시킬 것이 있다면 실행
}