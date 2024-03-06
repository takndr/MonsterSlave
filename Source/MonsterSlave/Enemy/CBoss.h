#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CBoss.generated.h"

UCLASS()
class MONSTERSLAVE_API ACBoss : public ACEnemy
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
	FORCEINLINE bool IsAblePhaseChange() { return bPhaseChange; }
	FORCEINLINE int32 GetCurrentPhase() { return BossPhase; }
	FORCEINLINE class ACBossBreath* GetBossBreath() { return BossBreath; }
	FORCEINLINE void SetPhaseChangeTrue() { bPhaseChange = true; }
	FORCEINLINE void SetPhaseChangeFalse() { bPhaseChange = false; }
	
	void ChangePhase();

	void SlashAttack();
	void BiteAttack();
	void BreathAttack();
	void EndAttack();

	void OnCollision(FName InName);
	void OffCollision(FName InName);

	void AttachHealthWidget();
	void SettingHealthWidget();

private:
	void Dead();
// =================================================================
public:
	bool bPhaseChange = false;
	int32 BossPhase = 0;

private:
	bool bFly = false;
	bool bHitNormal = false;
	bool bHitKnockBack = false;

public:
	bool bCanSlash = true;
	bool bCanBreath = true;

private:
	TSubclassOf<class UUserWidget> BossHpWidgetClass;
	class UCBossHp* BossHpWidget;
	class ACBossBreath* BossBreath;
// =================================================================
public:
	UFUNCTION()
		void OnSlashCoolDown();

	UFUNCTION()
		void OnBreathCoolDown();

	UFUNCTION()
		void RemoveHealthWidget();
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndDead();
// =================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Mouth;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Hand;

// =================================================================
public:
	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float SlashCoolDown = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float BreathCoolDown = 5.0f;

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
};
