#include "Items/Weapons/CEquipBow.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"

#include "Global.h"

ACEquipBow::ACEquipBow() {
	WeaponType = EWeaponType::Bow;
}

void ACEquipBow::Attack() {
	CheckNull(AttackMontage);
	CheckNull(AimAttackMontage);
	CheckNull(Owner);
	CLog::Log("Bow Attack");

	ACPlayer* player = Cast<ACPlayer>(Owner);
	CheckNull(player);

	if (player->IsAim()) {
		player->PlayAnimMontage(AimAttackMontage);
	}
	else {
		player->PlayAnimMontage(AttackMontage);
	}
}