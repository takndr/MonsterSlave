#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CInterfaceWeapon.generated.h"

UINTERFACE(MinimalAPI)
class UCInterfaceWeapon : public UInterface {
	GENERATED_BODY()
};

class MONSTERSLAVE_API ICInterfaceWeapon {
	GENERATED_BODY()

public:
	virtual void Attack() = 0;
};
