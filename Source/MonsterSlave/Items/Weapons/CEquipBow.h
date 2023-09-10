#pragma once

#include "CoreMinimal.h"
#include "Items/CEquipItem.h"
#include "CEquipBow.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipBow : public ACEquipItem
{
	GENERATED_BODY()
public:
	ACEquipBow();
protected:
	virtual void BeginPlay() override;
// =========================================================
public:
	virtual void OnAim() override;
	virtual void OffAim() override;
	virtual void Attack() override;
	virtual void EndAttack() override;
	virtual void Equipped() override;
	virtual void UnEquipped() override;

	void ShotArrow();
	void SpawnArrow();

	FORCEINLINE class ACArrow* GetArrow() { return Arrow; }
// =========================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* OnAimBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* OffAimBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* AttackBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* AimAttackBowMontage;
// =========================================================
private:
	TSubclassOf<ACArrow> ArrowClass;
	class ACArrow* Arrow;
};
