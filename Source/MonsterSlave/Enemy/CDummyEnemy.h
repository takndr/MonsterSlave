#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CDummyEnemy.generated.h"

UCLASS()
class MONSTERSLAVE_API ACDummyEnemy : public ACharacter
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
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE void ClearHittedCharacters() { HittedCharacters.Empty(); }

	void OnCollision();
	void OffCollision();
	void Attack();
	void EndAttack();

private:
	void Hitted(FDamageEvent const& DamageEvent);
	void Dead();
// =================================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void EndDead();
// =================================================================
public:
	TArray<class ACharacter*> HittedCharacters;
	
private:
	TSubclassOf<class UUserWidget> HPWidgetClass;
	float DamageValue;
// =================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HPWidget;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviorTree;


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
};
