#include "Component/CStatusComponent.h"

#include "Global.h"

UCStatusComponent::UCStatusComponent() {

}


void UCStatusComponent::BeginPlay() {
	Super::BeginPlay();

	CurrentHp = MaxHp;
}


void UCStatusComponent::IncreaseHealth(float Dx) {
	CurrentHp += Dx;
	CurrentHp = FMath::Clamp(CurrentHp, 0.0f, MaxHp);
}

void UCStatusComponent::DecreaseHealth(float Dx) {
	CurrentHp -= Dx;
	CurrentHp = FMath::Clamp(CurrentHp, 0.0f, MaxHp);
}

