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
	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(boss);

	ACBossBreath* breath = boss->GetBossBreath();
	CheckNull(breath);

	breath->OnCollision();
	breath->SetActivate(true);
}

void UCAnimNotifyStateBreath::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(boss);

	ACBossBreath* breath = boss->GetBossBreath();
	CheckNull(breath);

	breath->OffCollision();
	breath->SetActivate(false);
	
	boss->ClearHittedCharacters();
}
