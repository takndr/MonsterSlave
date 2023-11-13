#include "Component/CQuestComponent.h"

UCQuestComponent::UCQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCQuestComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

