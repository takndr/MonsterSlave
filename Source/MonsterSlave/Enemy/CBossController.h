#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CBossController.generated.h"

UCLASS()
class MONSTERSLAVE_API ACBossController : public AAIController
{
	GENERATED_BODY()
public:
	ACBossController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
// ==================================================================
public:
	FORCEINLINE class ACBoss* GetPossessedBoss() { return PossessedBoss; }
// ==================================================================
private:
	class ACBoss* PossessedBoss;
// ==================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;
};
