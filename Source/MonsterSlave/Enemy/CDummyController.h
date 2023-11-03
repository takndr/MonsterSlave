#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CDummyController.generated.h"

UCLASS()
class MONSTERSLAVE_API ACDummyController : public AAIController
{
	GENERATED_BODY()
public:
	ACDummyController();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
// ==================================================================
public:
	FORCEINLINE class ACDummyEnemy* GetPossessedDummy() { return PossessedDummy; }
// ==================================================================
private:
	UFUNCTION()
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
// ==================================================================
private:
	class ACDummyEnemy* PossessedDummy;
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
