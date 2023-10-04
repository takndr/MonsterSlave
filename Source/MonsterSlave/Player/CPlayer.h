#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/ItemStruct.h"
#include "CPlayer.generated.h"

UCLASS()
class MONSTERSLAVE_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
// ============================================================================
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddItem(const FCItemStruct& InItem);
	void RemoveInventoryItem(const FCItemStruct& InItem);
	void ReplaceInventoryItem(const FCItemStruct& OldItem, const FCItemStruct& NewItem);

	FORCEINLINE const bool IsAim() { return bAim; }

	UFUNCTION(BlueprintImplementableEvent, Exec)
		void TestPhaseChangeTrue();

	UFUNCTION(BlueprintImplementableEvent, Exec)
		void TestPhaseChangeFalse();

private:
	// Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
	void OnSwordWeapon();
	void OnBowWeapon();

	// Action Event
	void Inventory();
	void Attack();
	void PickUp();
	void OnAim();
	void OffAim();
// ============================================================================
private:
	UFUNCTION()
		void MeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void MeshComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
// ===========================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* MeshCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MeshSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* MinimapCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MinimapSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UPaperSpriteComponent* MinimapSprite;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* ActionComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* DeadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* UnarmedHeavyHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* UnarmedHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* SwordHeavyHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* SwordHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* BowHeavyHitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* BowHitMontage;
// ===========================================================
public:
	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	class UCInventory* InventoryWidget;

	bool bCanPickUp = false;
	bool bAim = false;

private:
	class USkeletalMesh* PlayerBody;
	class ACPlayerHair* PlayerHair;
	
	TSubclassOf<class UCPlayerHp> PlayerHpWidgetClass;
	class UCPlayerHp* PlayerHpWidget;

	class ACFieldItem* PickableActor;
	TArray<FCItemStruct> MyItems;
	int32 MaxItem = 15;

};
