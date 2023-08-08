#include "Component/CStatusComponent.h"

#include "Global.h"

UCStatusComponent::UCStatusComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	bEditableWhenInherited = true;

}


void UCStatusComponent::BeginPlay() {
	Super::BeginPlay();

	
}


void UCStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCStatusComponent::IncreaseHealth(float Dx) {
	//UKismetMathLibrary::ClampAngle();
}

void UCStatusComponent::DecreaseHealth(float Dx) {

}

