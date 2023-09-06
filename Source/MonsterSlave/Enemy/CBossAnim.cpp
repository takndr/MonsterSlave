#include "Enemy/CBossAnim.h"

#include "GameFramework/Character.h"

#include "Global.h"

void UCBossAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	// TODO : bFly가져오는 코드
}

void UCBossAnim::NativeBeginPlay() {
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());

}