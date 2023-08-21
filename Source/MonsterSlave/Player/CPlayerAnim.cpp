#include "CPlayerAnim.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"

#include "Global.h"

void UCPlayerAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);

	Speed = player->GetVelocity().Size2D();
	Direction = CalculateDirection(player->GetVelocity(), player->GetControlRotation());
	Pitch = player->GetBaseAimRotation().Pitch;
	WeaponType = player->GetWeaponType();
	bAim = player->IsAim();

}

void UCPlayerAnim::NativeBeginPlay() {
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());


}