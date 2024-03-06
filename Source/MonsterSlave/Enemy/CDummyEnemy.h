#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CDummyEnemy.generated.h"

UCLASS()
class MONSTERSLAVE_API ACDummyEnemy : public ACEnemy
{
	GENERATED_BODY()
public:
	ACDummyEnemy();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:	
	virtual void Tick(float DeltaTime) override;
// =================================================================
public:
	void OnCollision();
	void OffCollision();
	void Attack();
	void EndAttack();

private:
	void Hitted(AActor* DamageCauser);
	void Dead();
// =================================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void EndDead();

	UFUNCTION()
		void OffHpWidget();

	UFUNCTION()
		void OnSkillCoolDown();
// =================================================================
private:
	TSubclassOf<class UUserWidget> HPWidgetClass;
	bool bCanSkill = true;

	bool bHitNormal = false;
	bool bHitKnockback = false;
// =================================================================
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UWidgetComponent* HPWidget;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCapsuleComponent* Weapon;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "AttackMontage")
		class UAnimMontage* SkillMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* DieMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "OtherMontage")
		class UAnimMontage* KnockbackMontage;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float SkillCoolDown = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float SkillDamage = 30.0f;
};
