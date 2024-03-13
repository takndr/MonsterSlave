#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemStruct.h"
#include "CWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChangedSignature, EWeaponType, InPrevType, EWeaponType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponImageChangedSignature, UCItemData*, InItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCWeaponComponent();
protected:
	virtual void BeginPlay() override;
//===================================================================
public:
	void SetUnarmed();
	void SetSwordType();
	void SetBowType();

	void SetSword(class UCItemData* InItem);
	void SetBow(class UCItemData* InItem);

	void RemoveSword();
	void RemoveBow();

	void EquipSword();
	void EquipBow();
	void UnEquip();
	void OffAllCollisions();

	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE class UCItemData* GetSwordWeapon() { return Weapons[(int32)EWeaponType::Sword]; }
	FORCEINLINE class UCItemData* GetBowWeapon() { return Weapons[(int32)EWeaponType::Bow]; }

	FORCEINLINE bool IsUnarmed() { return WeaponType == EWeaponType::Unarmed; }
	FORCEINLINE bool IsEquipSword() { return WeaponType == EWeaponType::Sword; }
	FORCEINLINE bool IsEquipBow() { return WeaponType == EWeaponType::Bow; }
	FORCEINLINE bool IsSetSword() { return Weapons[(int32)EWeaponType::Sword] != nullptr; }
	FORCEINLINE bool IsSetBow() { return Weapons[(int32)EWeaponType::Bow] != nullptr; }

private:
	void ChangeType(EWeaponType InNewType);
//===================================================================
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE class UCItemData* GetCurrentWeapon() { return Weapons[(int32)WeaponType]; }

private:
	UFUNCTION()
		void SaveWeaponDatas();
//===================================================================

//===================================================================
public:	
	EWeaponType WeaponType = EWeaponType::Unarmed;
	class UCItemData* Weapons[(int32)EWeaponType::Max];
	
private:
	class ACharacter* OwnerCharacter;
//===================================================================
public:
	UPROPERTY(BlueprintAssignable)
		FWeaponTypeChangedSignature OnWeaponTypeChanged;

	UPROPERTY(BlueprintAssignable)
		FWeaponImageChangedSignature OnWeaponImageChanged;
};
