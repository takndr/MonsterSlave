#include "Notifies/CAnimNotifyBossFly.h"

#include "Enemy/CBoss.h"

#include "Global.h"

FString UCAnimNotifyBossFly::GetNotifyName_Implementation() const
{
	return "Fly";
}

void UCAnimNotifyBossFly::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);

	ACBoss* boss = Cast<ACBoss>(MeshComp->GetOwner());
	CheckNull(boss);

	UCStateComponent* stateComp = CHelpers::GetComponent<UCStateComponent>(boss);
	CheckNull(stateComp);

	boss->SetFly(true);
	// TODO : °íÄ¥Á¡
	boss->SetPhaseChangeFalse();
	stateComp->SetIdle();
}