#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Patrol, Rotate, Move, Action, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCBehaviorComponent();
protected:
	virtual void BeginPlay() override;
// ==================================================================
public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackBoard) { Blackboard = InBlackBoard; }

	void SetWaitMode();
	void SetRotateMode();
	void SetMoveMode();
	void SetActionMode();
	void SetPatrolMode();

	class ACPlayer* GetPlayerKey();
	FVector GetLocationKey();

private:
	EBehaviorType GetCurrentBehavior();
// ==================================================================
public:
	UFUNCTION(BlueprintCallable)
		bool IsWaitMode();

	UFUNCTION(BlueprintCallable)
		bool IsRotateMode();

	UFUNCTION(BlueprintCallable)
		bool IsMoveMode();

	UFUNCTION(BlueprintCallable)
		bool IsActionMode();

	UFUNCTION(BlueprintCallable)
		bool IsPatrolMode();
// ==================================================================
private:
	class UBlackboardComponent* Blackboard;
// ==================================================================
};
