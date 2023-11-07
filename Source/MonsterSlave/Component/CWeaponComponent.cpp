#include "Component/CWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Items/CEquipItem.h"

#include "Global.h"

UCWeaponComponent::UCWeaponComponent()
{

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCWeaponComponent::SetUnarmed()
{
	ChangeType(EWeaponType::Unarmed);
}

void UCWeaponComponent::SetSwordType()
{
	ChangeType(EWeaponType::Sword);
}

void UCWeaponComponent::SetBowType()
{
	ChangeType(EWeaponType::Bow);
}

void UCWeaponComponent::ChangeType(EWeaponType InNewType)
{
	EWeaponType prev = WeaponType;
	WeaponType = InNewType;

	if (OnWeaponTypeChanged.IsBound())
	{
		OnWeaponTypeChanged.Broadcast(prev, InNewType);
	}
}

void UCWeaponComponent::SetSword(ACEquipItem* InItem)
{
	Weapons[(int32)EWeaponType::Sword] = InItem;
}

void UCWeaponComponent::SetSword(const FCItemStruct& InItem)
{
	ACEquipItem* weapon;
	ACharacter* character = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters param;
	param.Owner = GetOwner();

	weapon = GetWorld()->SpawnActor<ACEquipItem>(InItem.EquipWeaponClass, param);
	weapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("sword_holster"));

	Weapons[(int32)EWeaponType::Sword] = weapon;
}

void UCWeaponComponent::SetBow(ACEquipItem* InItem)
{
	Weapons[(int32)EWeaponType::Bow] = InItem;
}

void UCWeaponComponent::SetBow(const FCItemStruct& InItem)
{
	ACEquipItem* weapon;
	ACharacter* character = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters param;
	param.Owner = GetOwner();

	weapon = GetWorld()->SpawnActor<ACEquipItem>(InItem.EquipWeaponClass, param);
	weapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("bow_holster"));

	Weapons[(int32)EWeaponType::Bow] = weapon;
}

void UCWeaponComponent::RemoveSword()
{
	Weapons[(int32)EWeaponType::Sword]->Destroy();
	Weapons[(int32)EWeaponType::Sword] = nullptr;
}

void UCWeaponComponent::RemoveBow()
{
	Weapons[(int32)EWeaponType::Bow]->Destroy();
	Weapons[(int32)EWeaponType::Bow] = nullptr;
}

void UCWeaponComponent::EquipSword()
{
	SetSwordType();
	Weapons[(int32)EWeaponType::Sword]->Equip();
}

void UCWeaponComponent::EquipBow()
{
	SetBowType();
	Weapons[(int32)EWeaponType::Bow]->Equip();
}

void UCWeaponComponent::UnEquip()
{
	Weapons[(int32)WeaponType]->UnEquip();
	SetUnarmed();
}