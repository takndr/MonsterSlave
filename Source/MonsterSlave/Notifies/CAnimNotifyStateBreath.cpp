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
	// Breath�� Collision �ѱ�
	// Breath�� Particle �ѱ�
}

void UCAnimNotifyStateBreath::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// Breath�� Collision ����
	// Breath�� Particle ����
}
