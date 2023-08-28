#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8 {
	Idle, Equip, Attack, Evade, Inventory
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
	FORCEINLINE bool IsAttack() { return State == EStateType::Attack; }
	FORCEINLINE bool IsEavde() { return State == EStateType::Evade; }

	FORCEINLINE void SetIdle() { State = EStateType::Idle; }
	FORCEINLINE void SetEquip() { State = EStateType::Equip; }
	FORCEINLINE void SetAttack() { State = EStateType::Attack; }
	FORCEINLINE void SetEvade() { State = EStateType::Evade; }
//===================================================================

//===================================================================
private:
	EStateType State;
		
};
