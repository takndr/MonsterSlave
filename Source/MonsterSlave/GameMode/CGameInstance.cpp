#include "GameMode/CGameInstance.h"

#include "GameMode/CSaveGame.h"

void UCGameInstance::Shutdown()
{
	//if (OnGameSave.IsBound())
	//{
	//	OnGameSave.Broadcast();
	//}

	Super::Shutdown();
}