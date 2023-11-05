#include "Notifies/CAnimNotifyEndAttack.h"

#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"
#include "Component/CWeaponComponent.h"
#include "Component/CStateComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const
{
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{
		UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
		CheckNull(weaponComp);

		ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
		CheckNull(equipItem);

		equipItem->EndAttack();
	}

	if (!!Cast<ACBoss>(MeshComp->GetOwner()))
	{
		ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
		CheckNull(boss);

		boss->EndAttack();
	}

	if (!!Cast<ACDummyEnemy>(MeshComp->GetOwner()))
	{
		ACDummyEnemy* enemy = Cast<ACDummyEnemy>(MeshComp->GetOwner());
		CheckNull(enemy);

		enemy->EndAttack();
	}
}
