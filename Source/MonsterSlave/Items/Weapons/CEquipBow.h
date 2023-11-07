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
	virtual void FirstSkill() override;
	virtual void SecondSkill() override;

	void SpawnArrow();

// =========================================================
private:
	UFUNCTION()
		void SpawnArrowRain();
// =========================================================
private:
	TSubclassOf<class ACArrow> ArrowClass;
	TSubclassOf<class ACArrowRain> ArrowRainClass;
	class ACArrow* Arrow;
// =========================================================
private:
	UPROPERTY(EditDefaultsOnly)
		float ArrowRainRange = 700.0f;


};
