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
public:
	UPROPERTY(EditDefaultsOnly)
		class UPaperSpriteComponent* MinimapSprite;

	UPROPERTY(EditDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	UPROPERTY(EditDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(EditDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly)
		class UCActionComponent* ActionComponent;

protected:
	

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* MeshCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MeshSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* MinimapCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MinimapSpringArm;
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
