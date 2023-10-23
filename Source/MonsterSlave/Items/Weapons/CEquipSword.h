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
	void OnCollision();
	void OffCollision();
// =========================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// =========================================================

// =========================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;
};
