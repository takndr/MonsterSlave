#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait, Patrol, Rotate, Move, Action, Slash, Breath, Max
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
	void SetPatrolMode();
	void SetRotateMode();
	void SetMoveMode();
	void SetActionMode();
	void SetSlashMode();
	void SetBreathMode();

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

	UFUNCTION(BlueprintCallable)
		bool IsSlashMode();

	UFUNCTION(BlueprintCallable)
		bool IsBreathMode();
// ==================================================================
private:
	class UBlackboardComponent* Blackboard;
// ==================================================================
};
