#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBoss.generated.h"

UCLASS()
class MONSTERSLAVE_API ACBoss : public ACharacter
{
	GENERATED_BODY()

public:
	ACBoss();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:	
	virtual void Tick(float DeltaTime) override;
// =================================================================
public:
	FORCEINLINE void SetFly(bool InFly) { bFly = InFly; }
	FORCEINLINE bool IsFly() { return bFly; }

// =================================================================
private:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
	int32 BossPhase = 1;
	bool bFly = false; 

	TSubclassOf<class UUserWidget> BossHpWidgetClass;
	class UCBossHp* BossHpWidget;
// =================================================================
public:
	UFUNCTION(BlueprintCallable)
		void BossFly();

	UFUNCTION(BlueprintCallable)
		void BossLand();
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;

// =================================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* LandFlameMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* FlyFlameMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* AttackHandMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* AttackMouthMontage;

	UPROPERTY(EditDefaultsOnly, Category = "FlyMontage")
		class UAnimMontage* LandMontage;

	UPROPERTY(EditDefaultsOnly, Category = "FlyMontage")
		class UAnimMontage* FlyMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* DieMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* ScreamMontage;
};
