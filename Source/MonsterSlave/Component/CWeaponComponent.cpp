#include "Component/CWeaponComponent.h"

#include "Global.h"

UCWeaponComponent::UCWeaponComponent() {

}


void UCWeaponComponent::BeginPlay() {
	Super::BeginPlay();

	
}

void UCWeaponComponent::SetUnarmed() {
	WeaponType = EWeaponType::Unarmed;


}

void UCWeaponComponent::SetSword() {
	WeaponType = EWeaponType::Sword;

	//Weapons[] = ;
}

void UCWeaponComponent::SetBow() {
	WeaponType = EWeaponType::Bow;


}
