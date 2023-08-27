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

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddItem(const FCItemStruct& InItem);
	void RemoveInventoryItem(const FCItemStruct& InItem);
	void ReplaceInventoryItem(const FCItemStruct& OldItem, const FCItemStruct& NewItem);

	void EquipSword(const FCItemStruct& InItem);
	void EquipBow(const FCItemStruct& InItem);
	void UnEquipSword();
	void UnEquipBow();

	FORCEINLINE void SetCurrentWeapon(class ACEquipItem* InWeapon) { CurrentWeapon = InWeapon; }
	FORCEINLINE class ACEquipItem* GetCurrentWeapon() { return CurrentWeapon; }
	FORCEINLINE const bool IsAim() { return bAim; }

	FORCEINLINE void SetWeaponType(const EWeaponType InType) { WeaponType = InType; }
	FORCEINLINE const EWeaponType GetWeaponType() { return WeaponType; }

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void MeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void MeshComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


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

	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	class UCInventory* InventoryWidget;

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

	

public:
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

	// Weapons
	EWeaponType WeaponType = EWeaponType::Unarmed;
	class ACEquipItem* SwordWeapon;
	class ACEquipItem* BowWeapon;
	class ACEquipItem* CurrentWeapon;
};
