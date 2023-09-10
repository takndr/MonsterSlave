#pragma once

#include "CoreMinimal.h"
#include "Items/CEquipItem.h"
#include "CEquipSword.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipSword : public ACEquipItem {
	GENERATED_BODY()
	
public:
	ACEquipSword();
protected:
	virtual void BeginPlay() override;
// =========================================================
public:
	virtual void Attack() override;
	virtual void EndAttack() override;
	void NextCombo();
	void OnCollision();
	void OffCollision();

	FORCEINLINE void EnabledCombo() { bCanCombo = true; }
	FORCEINLINE void DisabledCombo() { bCanCombo = false; }
// =========================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// =========================================================
private:
	TArray<AActor*> HittedActors;
	bool bCanCombo = false;
	bool bSucceed = false;
// =========================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;
};
