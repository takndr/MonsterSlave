#pragma once

#include "CoreMinimal.h"
#include "Items/CEquipItem.h"
#include "CEquipSword.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipSword : public ACEquipItem {
	GENERATED_BODY()
	

// =========================================================

private:
	class UCapsuleComponent* Capsule;
};
