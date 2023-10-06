#include "Notifies/CAnimNotifyStateBreath.h"

#include "Enemy/CBoss.h"
#include "etc/CBossBreath.h"

#include "Global.h"

FString UCAnimNotifyStateBreath::GetNotifyName_Implementation() const
{
	return "Breath";
}

void UCAnimNotifyStateBreath::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	// Breath의 Collision 켜기
	// Breath의 Particle 켜기
}

void UCAnimNotifyStateBreath::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Breath의 Collision 끄기
	// Breath의 Particle 끄기
}
