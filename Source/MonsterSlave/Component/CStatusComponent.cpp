#include "Component/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}


void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHp = MaxHp;
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	UCharacterMovementComponent* movementComponent = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(movementComponent);

	movementComponent->MaxWalkSpeed = MoveSpeed;
}


void UCStatusComponent::IncreaseHealth(float Dx)
{
	CurrentHp += Dx;
	CurrentHp = FMath::Clamp(CurrentHp, 0.0f, MaxHp);
}

void UCStatusComponent::DecreaseHealth(float Dx)
{
	CurrentHp -= Dx;
	CurrentHp = FMath::Clamp(CurrentHp, 0.0f, MaxHp);
}

