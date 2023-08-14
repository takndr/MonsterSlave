#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CWeaponInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class MONSTERSLAVE_API ICWeaponInterface
{
	GENERATED_BODY()

public:
	virtual void Attack() = 0;
};
