#include "Notifies/CAnimNotifyEndAttack.h"

#include "Component/CStateComponent.h"

#include "Global.h"


FString UCAnimNotifyEndAttack::GetNotifyName_Implementation() const {
	return "EndAttack";
}

void UCAnimNotifyEndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::Notify(MeshComp, Animation);

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(state);

	state->SetIdle();
}
// 활 EndAttack같은 경우에는 화살까지 재스폰 시켜야함