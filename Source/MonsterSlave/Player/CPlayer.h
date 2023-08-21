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
	FORCEINLINE void SetWeaponType(const EWeaponType InType) { WeaponType = InType; }
	FORCEINLINE const EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE const bool IsAim() { return bAim; }

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
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		class UPaperSpriteComponent* MinimapSprite;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		class UCStatusComponent* StatusComponent;

	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	class UCInventory* InventoryWidget;

protected:
	

private:
	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* MeshCamera;

	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* MeshSpringArm;

	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* MinimapCamera;

	UPROPERTY(VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
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
	EWeaponType WeaponType = EWeaponType::None;
	class ACEquipItem* SwordWeapon;
	class ACEquipItem* BowWeapon;
	class ACEquipItem* CurrentWeapon;
};
