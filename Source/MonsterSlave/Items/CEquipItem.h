#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "Interface/CInterfaceWeapon.h"
#include "CEquipItem.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipItem : public AActor, public ICInterfaceWeapon
{
	GENERATED_BODY()
	
public:	
	ACEquipItem();
	virtual void Tick(float DeltaTime) override;
	virtual void Attack() override;

	// CPlayer에서 1번이나 2번 눌렀을 때 호출하는 함수
	void Equip();
	void UnEquip();

	void Attach();
	void Detach();
	virtual void Equipped();
	void UnEquipped();
	virtual void OnAim();
	virtual void OffAim();
	

protected:
	virtual void BeginPlay() override;

private:	
	

// ===================================================
public:
	int32 ComboCount = 0;

protected:
	class ACharacter* Owner;
	EWeaponType WeaponType;		// 자식에서 초기화

private:
	class UCStateComponent* StateComp;
	class UCWeaponComponent* WeaponComp;
	bool bEquipping;

// ===================================================

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Attack") // -> Tarray로
		TArray<class UAnimMontage*> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack") // -> Tarray로
		TArray<class UAnimMontage*> AimAttackMontage;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		FName UnEquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		FName EquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		class UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		class UAnimMontage* OnAimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
		class UAnimMontage* OffAimMontage;

	

};
