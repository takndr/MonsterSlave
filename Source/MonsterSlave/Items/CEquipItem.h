#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "CEquipItem.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipItem();
	virtual void Tick(float DeltaTime) override;

	// CPlayer에서 1번이나 2번 눌렀을 때 호출하는 함수
	void Equip();
	void UnEquip();

	void Attach();
	void Detach();
	void Equipped();
	void UnEquipped();

protected:
	virtual void BeginPlay() override;

private:	
	

// ===================================================

protected:
	class ACharacter* Owner;
	EWeaponType WeaponType;		// 자식에서 초기화

private:
	bool bEquip;

// ===================================================

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly)
		FName UnEquippedHolster;

	UPROPERTY(EditDefaultsOnly)
		FName EquippedHolster;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* UnEquipMontage;

};
