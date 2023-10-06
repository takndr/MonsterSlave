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
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE bool IsAblePhaseChange() { return bPhaseChange; }
	FORCEINLINE int32 GetCurrentPhase() { return BossPhase; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }
	FORCEINLINE void SetHeavyHit(bool InHit) { bHeavyHit = InHit; }
	FORCEINLINE bool IsHeavyHit() { return bHeavyHit; }
	FORCEINLINE class ACBossBreath* GetBossBreath() { return BossBreath; }

	void ChangePhase();

	void SlashAttack();
	void BiteAttack();
	void BreathAttack();

	void OnCollision(FName InName);
	void OffCollision(FName InName);

// =================================================================
public:
	bool bPhaseChange = false;
	int32 BossPhase = 0;

private:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;

private:
	bool bFly = false;
	bool bHeavyHit = false;

public:
	TArray<class ACharacter*> HittedCharacters;

private:
	TSubclassOf<class UUserWidget> BossHpWidgetClass;
	class UCBossHp* BossHpWidget;
	class ACBossBreath* BossBreath;
// =================================================================
public:
	UFUNCTION(BlueprintCallable)
		void SetPhaseChangeTrue() { bPhaseChange = true; }

	UFUNCTION(BlueprintCallable)
		void SetPhaseChangeFalse() { bPhaseChange = false; }

private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// =================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Mouth;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Hand;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;

// =================================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* LandFlameMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* FlyFlameMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* AttackSlashMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* AttackBiteMontage;

	UPROPERTY(EditDefaultsOnly, Category = "PhaseChangeMontage")
		TArray<class UAnimMontage*> PhaseChangeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* DieMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* ScreamMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Details")
		FText BossName;

};
