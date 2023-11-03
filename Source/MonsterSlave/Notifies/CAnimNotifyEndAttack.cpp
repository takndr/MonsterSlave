#include "Notifies/CAnimNotifyEndAttack.h"

#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"
#include "Component/CWeaponComponent.h"
#include "Component/CStateComponent.h"
#include "Items/CEquipItem.h"

#include "Global.h"

FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const {
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	// TODO : Boss�� �̿� �����ϰ� �����ߴµ�, ������ ��ü������ �ٲ����
	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);
	stateComp->SetIdle();

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);

	ACEquipItem* equipItem = weaponComp->GetCurrentWeapon();
	CheckNull(equipItem);

	equipItem->EndAttack();


	if (!!Cast<ACPlayer>(MeshComp->GetOwner()))
	{

	}

	if (!!Cast<ACBoss>(MeshComp->GetOwner()))
	{

	}

	if (!!Cast<ACDummyEnemy>(MeshComp->GetOwner()))
	{

	}
}
