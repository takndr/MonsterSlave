#include "Component/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameMode/CSaveGame.h"

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

	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	// 저장된 정보 있으면 저장
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	if (saveGame != nullptr)
	{
		MaxHp = saveGame->MaxHp;
		CurrentHp = saveGame->CurrentHp;
		movementComponent->MaxWalkSpeed = saveGame->MoveSpeed;
	}
	else
	{
		CurrentHp = MaxHp;
		movementComponent->MaxWalkSpeed = MoveSpeed;
	}
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

