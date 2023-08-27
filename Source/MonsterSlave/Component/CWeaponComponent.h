#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemStruct.h"
#include "CWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCWeaponComponent : public UActorComponent {
	GENERATED_BODY()
public:	
	UCWeaponComponent();
protected:
	virtual void BeginPlay() override;
//===================================================================
public:
	void SetUnarmed();
	void SetSword();
	void SetBow();

	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
//===================================================================

//===================================================================

//===================================================================
public:	
	EWeaponType WeaponType = EWeaponType::Unarmed;
	

private:
	class ACEquipItem* Weapons[(int32)EWeaponType::Max];
		
};
