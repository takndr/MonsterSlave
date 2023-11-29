#include "Component/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameMode/CSaveGame.h"
#include "etc/CPortal.h"

#include "Player/CPlayer.h"
#include "Widgets/Player/CPlayerStatus.h"

#include "Global.h"

UCStatusComponent::UCStatusComponent()
{

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	UCharacterMovementComponent* movementComponent = CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter);
	CheckNull(movementComponent);

	CurrentHp = MaxHp;
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
