#include "CPlayerAnim.h"

#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CWeaponComponent.h"

#include "Global.h"

void UCPlayerAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);
	CheckNull(WeaponComponent);

	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);

	Speed = player->GetVelocity().Size2D();
	Direction = CalculateDirection(player->GetVelocity(), player->GetControlRotation());
	Pitch = player->GetBaseAimRotation().Pitch;
	bAim = player->IsAim();

	WeaponType = WeaponComponent->GetWeaponType();
}

void UCPlayerAnim::NativeBeginPlay() {
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(TryGetPawnOwner());

}