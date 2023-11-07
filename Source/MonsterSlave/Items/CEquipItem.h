#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "Components/TimeLineComponent.h"
#include "CEquipItem.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipItem : public AActor
{
	GENERATED_BODY()
public:	
	ACEquipItem();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
// ===================================================
public:
	virtual void Attack();
	virtual void NextCombo();
	virtual void EndAttack();
	virtual void FirstSkill();
	virtual void SecondSkill();

	void Equip();
	void UnEquip();

	void Attach();
	void Detach();

	virtual void Equipped();
	virtual void UnEquipped();

	FORCEINLINE void EnabledCombo() { bCanCombo = true; }
	FORCEINLINE void DisabledCombo() { bCanCombo = false; }
private:	

// ===================================================
private:
	UFUNCTION()
		void Dissolving(float Output);
// ===================================================
public:
	int32 ComboCount = 0;

protected:
	class ACharacter* Owner;
	EWeaponType WeaponType;		// 자식에서 초기화
	TArray<AActor*> HittedActors;

protected:
	class UCStateComponent* StateComp;
	class UCWeaponComponent* WeaponComp;
	bool bEquipping = false;

private:
	class UMaterialInstanceDynamic* DynamicMaterial;
	bool bCanCombo = false;
	bool bSucceed = false;
	bool bCanFirstSkill = true;
	bool bCanSecondSkill = true;

	class UCurveFloat* DissolveCurve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;
// ===================================================
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		TArray<class UAnimMontage*> AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* FirstSkillMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		class UAnimMontage* SecondSkillMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName UnEquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName EquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Equip/UnEquip")
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Equip/UnEquip")
		class UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float FirstSkillCoolDown;

	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float SecondSkillCoolDown;
};
