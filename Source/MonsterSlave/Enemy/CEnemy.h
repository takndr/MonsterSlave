#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemy.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEnemy : public ACharacter
{
	GENERATED_BODY()
public:
	ACEnemy();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:	
	virtual void Tick(float DeltaTime) override;
// =================================================================
public:
	FORCEINLINE FText GetEnemyName() { return EnemyName; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }
	FORCEINLINE bool IsHitNormal() { return bHitNormal; }
	FORCEINLINE bool IsHitKnockBack() { return bHitKnockBack; }
// =================================================================
protected:

// =================================================================
public:
	TArray<class ACharacter*> HittedCharacters;		// public인 이유? 확인해봐야함

protected:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue = 0.0f;

	bool bHitNormal = false;
	bool bHitKnockBack = false;
// =================================================================
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCStateComponent* StateComponent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Names")
		FText EnemyName;
};
