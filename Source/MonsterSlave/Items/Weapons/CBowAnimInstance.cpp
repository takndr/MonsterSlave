#include "Items/Weapons/CBowAnimInstance.h"

#include "Player/CPlayer.h"
#include "Items/CEquipItem.h"

#include "Global.h"

void UCBowAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	//
	CheckNull(OwnerCharacter);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	CheckNull(player);

	bAim = player->IsAim();

}

void UCBowAnimInstance::NativeBeginPlay() {
	Super::NativeBeginPlay();

}