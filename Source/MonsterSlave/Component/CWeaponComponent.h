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
	void SetSword(class ACEquipItem* InItem);
	void SetSword(const FCItemStruct& InItem);
	void SetBow(class ACEquipItem* InItem);
	void SetBow(const FCItemStruct& InItem);
	void RemoveSword();
	void RemoveBow();
	void EquipSword();
	void EquipBow();

	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE bool IsSetSword() { return Weapons[(int32)EWeaponType::Sword] != nullptr; }
	FORCEINLINE bool IsSetBow() { return Weapons[(int32)EWeaponType::Bow] != nullptr; }

//===================================================================

//===================================================================

//===================================================================
public:	
	EWeaponType WeaponType = EWeaponType::Unarmed;
	class ACEquipItem* Weapons[(int32)EWeaponType::Max];
	

private:
		
};
