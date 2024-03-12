#include "GameMode/CGameMode.h"

#include "GameMode/CGameInstance.h"
#include "GameMode/CSaveGame.h"

#include "Global.h"

void ACGameMode::Logout(AController* Exiting)
{

	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CheckNull(gameInstance);

	if (gameInstance->OnGameSave.IsBound())
	{
		CLog::Log("Save Broadcast");
		gameInstance->OnGameSave.Broadcast();
	}

	Super::Logout(Exiting);
}