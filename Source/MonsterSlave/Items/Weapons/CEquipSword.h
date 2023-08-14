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

private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// =========================================================

private:
	class UCapsuleComponent* Capsule;
};
