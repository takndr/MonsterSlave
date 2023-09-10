#include "Enemy/CBossAnim.h"

#include "GameFramework/Character.h"
#include "Enemy/CBoss.h"

#include "Global.h"

void UCBossAnim::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	ACBoss* boss = Cast<ACBoss>(OwnerCharacter);
	bFly = boss->IsFly();
}

void UCBossAnim::NativeBeginPlay() {
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());


}