#include "Component/CWeaponComponent.h"

#include "GameFramework/Character.h"

#include "GameMode/CSaveGame.h"
#include "Items/CEquipItem.h"


#include "Player/CPlayer.h"
#include "Global.h"

UCWeaponComponent::UCWeaponComponent()
{

}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// 저장된 정보 있으면 저장
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	CheckNull(saveGame);

	if(saveGame->SwordItem.Name != "NULL")
	{
		SetSword((saveGame->SwordItem));
	}

	if(saveGame->BowItem.Name != "NULL")
	{
		SetBow((saveGame->BowItem));
	}

	if(saveGame->WeaponType != EWeaponType::Unarmed)
	{
		ChangeType(saveGame->WeaponType);
		Weapons[(int32)saveGame->WeaponType]->Equip();
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

void UCWeaponComponent::SetSword(const FCItemStruct& InItem)
{
	ACEquipItem* weapon;
	ACharacter* character = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters param;
	param.Owner = GetOwner();

	weapon = GetWorld()->SpawnActor<ACEquipItem>(InItem.EquipWeaponClass, param);
	weapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("sword_holster"));
	weapon->Item = InItem;

	Weapons[(int32)EWeaponType::Sword] = weapon;
}

void UCWeaponComponent::SetBow(const FCItemStruct& InItem)
{
	ACEquipItem* weapon;
	ACharacter* character = Cast<ACharacter>(GetOwner());

	FActorSpawnParameters param;
	param.Owner = GetOwner();

	weapon = GetWorld()->SpawnActor<ACEquipItem>(InItem.EquipWeaponClass, param);
	weapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("bow_holster"));
	weapon->Item = InItem;

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