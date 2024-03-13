#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemStruct.h"
#include "Components/TimeLineComponent.h"
#include "CEquipItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFirstSkillSignature, float, InCoolDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSecondSkillSignature, float, InCoolDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOffFirstSkillSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOffSecondSkillSignature);

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
	virtual void FirstSkill();
	virtual void SecondSkill();

	virtual void OnCollision() {}
	virtual void OffCollision() {}

	void Equip();
	void UnEquip();

	void Attach();
	void Detach();

	void SetHitNormal();
	void SetHitKnockBack();

	FORCEINLINE void EnabledCombo() { bCanCombo = true; }
	FORCEINLINE void DisabledCombo() { bCanCombo = false; }
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE bool IsNormalHit() { return bNormal; }
	FORCEINLINE bool IsKnockBackHit() { return bKnockBack; }
// ===================================================
public:
	UFUNCTION(BlueprintCallable)
		virtual void EndAttack();

private:
	UFUNCTION()
		void Dissolving(float Output);

	UFUNCTION()
		void EndFirstSkillCool();

	UFUNCTION()
		void EndSecondSkillCool();

// ===================================================
public:
	FCItemStruct Item;
	int32 ComboCount = 0;

protected:
	class ACharacter* OwnerCharacter;
	EWeaponType WeaponType;		// 자식에서 초기화
	TArray<AActor*> HittedActors;

protected:
	class UCStateComponent* StateComp;
	class UCWeaponComponent* WeaponComp;
	bool bEquipping = false;
	bool bNormal = false;
	bool bKnockBack = false;
	bool bCanFirstSkill = true;
	bool bCanSecondSkill = true;

private:
	class UMaterialInstanceDynamic* DynamicMaterial;
	bool bCanCombo = false;
	bool bSucceed = false;

	class UCurveFloat* DissolveCurve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;

	float FirstSkillTemp;
	float SecondSkillTemp;
	
// ===================================================
public:
	UPROPERTY(BlueprintAssignable)
		FFirstSkillSignature OnFirstSkillCoolDown;
	
	UPROPERTY(BlueprintAssignable)
		FSecondSkillSignature OnSecondSkillCoolDown;

	UPROPERTY(BlueprintAssignable)
		FOffFirstSkillSignature OffFirstSkillCoolDown;

	UPROPERTY(BlueprintAssignable)
		FOffSecondSkillSignature OffSecondSkillCoolDown;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName UnEquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName EquippedHolster;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
		TSubclassOf<class UCameraShakeBase> ShakeClass;

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

	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float FirstSkillCoolDown = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "CoolDown")
		float SecondSkillCoolDown = 10.0f;
};
