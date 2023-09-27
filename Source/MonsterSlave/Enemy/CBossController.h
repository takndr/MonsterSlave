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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
// ==================================================================
public:
	FORCEINLINE class ACBoss* GetPossessedBoss() { return PossessedBoss; }
// ==================================================================
private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
// ==================================================================
private:
	class ACBoss* PossessedBoss;
	class UAISenseConfig_Sight* SightPerception;

	
// ==================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(EditAnywhere)
		float BehaviorRange = 150.0f;

	UPROPERTY(EditAnywhere)
		bool bDebugMode = true;


};
