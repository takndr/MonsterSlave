#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/CWeaponComponent.h"
#include "CActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();
protected:
	virtual void BeginPlay() override;
// ==================================================================
public:
	void Action();
// ==================================================================

// ==================================================================
 
// ==================================================================
		
};
