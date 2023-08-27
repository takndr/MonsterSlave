#include "Items/Weapons/CBowAnimInstance.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"

#include "Global.h"

void UCBowAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	//
	CheckNull(OwnerCharacter);

	CLog::Log("Bow Check Player2");
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	CheckNull(player);

	CLog::Log("Bow Check Player3");
	bAim = player->IsAim();

}

void UCBowAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();

	ACEquipItem* OwnerItem = Cast<ACEquipItem>(TryGetPawnOwner());
	CheckNull(OwnerItem);
	CLog::Log("Bow Anim Begin Play2");
	OwnerCharacter = Cast<ACPlayer>(OwnerItem->GetOwner());

}