#include "Component/CStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameMode/CSaveGame.h"
#include "etc/CPortal.h"

#include "Player/CPlayer.h"

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

	// 저장된 정보 있으면 저장
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	if (saveGame != nullptr && Cast<ACPlayer>(OwnerCharacter) != nullptr)
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

	// 포탈에 저장 관련 델리게이트 바인딩
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPortal::StaticClass(), outActors);
	for (auto outActor : outActors)
	{
		ACPortal* outPortal = Cast<ACPortal>(outActor);
		if (outPortal == nullptr) continue;

		outPortal->OnPortalSave.AddDynamic(this, &UCStatusComponent::SaveStatusDatas);
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

void UCStatusComponent::SaveStatusDatas()
{
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	CheckNull(player);

	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	if (Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0)) != nullptr)
	{
		saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	}

	saveGame->MaxHp = MaxHp;
	saveGame->CurrentHp = CurrentHp;
	saveGame->MoveSpeed = MoveSpeed;

	UGameplayStatics::SaveGameToSlot(saveGame, "Test", 0);
}