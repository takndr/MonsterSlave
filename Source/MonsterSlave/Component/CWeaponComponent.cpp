#include "Component/CWeaponComponent.h"

#include "GameFramework/Character.h"

#include "GameMode/CSaveGame.h"
#include "Items/CEquipItem.h"
#include "Items/CItemData.h"

#include "Player/CPlayer.h"
#include "Global.h"

UCWeaponComponent::UCWeaponComponent()
{

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	// 저장된 정보 있으면 저장
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	CheckNull(saveGame);

	CheckNull(Cast<ACPlayer>(OwnerCharacter));
	if(saveGame->SwordItem != nullptr)
	{
		SetSword((saveGame->SwordItem));
	}

	if(saveGame->BowItem != nullptr)
	{
		SetBow((saveGame->BowItem));
	}

	if(saveGame->WeaponType != EWeaponType::Unarmed)
	{
		ChangeType(saveGame->WeaponType);
		Weapons[(int32)saveGame->WeaponType]->GetEquipItem()->Equip();
	}
	
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

void UCWeaponComponent::SetSword(class UCItemData* InItem)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	Weapons[(int32)EWeaponType::Sword] = InItem;

	InItem->SpawnEquipItem(GetWorld(), character);
}

void UCWeaponComponent::SetBow(class UCItemData* InItem)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	Weapons[(int32)EWeaponType::Bow] = InItem;

	InItem->SpawnEquipItem(GetWorld(), character);
}

void UCWeaponComponent::RemoveSword()
{
	Weapons[(int32)EWeaponType::Sword]->GetEquipItem()->Destroy();
	Weapons[(int32)EWeaponType::Sword] = nullptr;
}

void UCWeaponComponent::RemoveBow()
{
	Weapons[(int32)EWeaponType::Bow]->GetEquipItem()->Destroy();
	Weapons[(int32)EWeaponType::Bow] = nullptr;
}

void UCWeaponComponent::EquipSword()
{
	SetSwordType();
	Weapons[(int32)EWeaponType::Sword]->GetEquipItem()->Equip();
}

void UCWeaponComponent::EquipBow()
{
	SetBowType();
	Weapons[(int32)EWeaponType::Bow]->GetEquipItem()->Equip();
}

void UCWeaponComponent::UnEquip()
{
	Weapons[(int32)WeaponType]->GetEquipItem()->UnEquip();
	SetUnarmed();
}