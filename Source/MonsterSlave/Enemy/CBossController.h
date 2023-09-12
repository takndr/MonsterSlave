#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CBossController.generated.h"

UCLASS()
class MONSTERSLAVE_API ACBossController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
