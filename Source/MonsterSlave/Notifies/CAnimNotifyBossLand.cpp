#include "Notifies/CAnimNotifyBossLand.h"

#include "Enemy/CBoss.h"
#include "Component/CStateComponent.h"

#include "Global.h"

FString UCAnimNotifyBossLand::GetNotifyName_Implementation() const {
	return "LandOff";
}


void UCAnimNotifyBossLand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(boss);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(boss);
	CheckNull(stateComp);

	boss->SetFly(false);
	// TODO : °íÄ¥Á¡
	boss->SetPhaseChangeFalse();
	stateComp->SetIdle();
}