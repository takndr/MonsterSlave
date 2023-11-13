#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8 
{
	Idle, Equip, Action, Evade, Dead, Wait
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCStateComponent();
protected:
	virtual void BeginPlay() override;
//===================================================================
public:	
	FORCEINLINE bool IsIdle() { return State == EStateType::Idle; }
	FORCEINLINE bool IsEquip() { return State == EStateType::Equip; }
	FORCEINLINE bool IsAction() { return State == EStateType::Action; }
	FORCEINLINE bool IsEavde() { return State == EStateType::Evade; }
	FORCEINLINE bool IsDead() { return State == EStateType::Dead; }
	FORCEINLINE bool IsWait() { return State == EStateType::Wait; }

	FORCEINLINE void SetIdle() { State = EStateType::Idle; }
	FORCEINLINE void SetEquip() { State = EStateType::Equip; }
	FORCEINLINE void SetAction() { State = EStateType::Action; }
	FORCEINLINE void SetEvade() { State = EStateType::Evade; }
	FORCEINLINE void SetDead() { State = EStateType::Dead; }
	FORCEINLINE void SetWait() { State = EStateType::Wait; }
//===================================================================

//===================================================================
private:
	EStateType State;
		
};
