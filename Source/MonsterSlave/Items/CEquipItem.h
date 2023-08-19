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

	// CPlayer���� 1���̳� 2�� ������ �� ȣ���ϴ� �Լ�
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
	EWeaponType WeaponType;		// �ڽĿ��� �ʱ�ȭ

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
