#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS()
class MONSTERSLAVE_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void Logout(AController* Exiting) override;
};
