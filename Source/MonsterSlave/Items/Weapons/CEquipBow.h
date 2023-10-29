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
	virtual void Attack() override;
	virtual void Equipped() override;
	virtual void UnEquipped() override;

	void SpawnArrow();
// =========================================================
private:

// =========================================================
private:
	//TSubclassOf<ACArrow> ArrowClass;
	//class ACArrow* Arrow;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> ArrowClass;

	class AActor* Arrow;
};
