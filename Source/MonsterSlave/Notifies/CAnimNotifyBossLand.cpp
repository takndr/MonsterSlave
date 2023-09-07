#include "Notifies/CAnimNotifyBossLand.h"

#include "Enemy/CBoss.h"

#include "Global.h"

FString UCAnimNotifyBossLand::GetNotifyName_Implementation() const {
	return "LandOff";
}


void UCAnimNotifyBossLand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(boss);

	boss->SetFly(false);
}