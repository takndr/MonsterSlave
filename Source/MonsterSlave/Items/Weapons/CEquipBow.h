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
	virtual void OnAim() override;
	virtual void OffAim() override;
	virtual void Attack() override;
	virtual void Equipped() override;

	void SpawnArrow();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* OnAimBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* OffAimBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* AttackBowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Bow")
		class UAnimMontage* AimAttackBowMontage;

private:
	class ACArrow* Arrow;
};
