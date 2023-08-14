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
	void AddItem(FCItemStruct InItem);
	void RemoveItem(FCItemStruct InItem);

protected:
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void MeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void MeshComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Exec)
		void DamageTest(float Damage);

private:
	// Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);

	// Action Event
	void Inventory();
	void Attack();
	void PickUp();

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

private:
	class USkeletalMesh* PlayerBody;
	class ACPlayerHair* PlayerHair;

	TSubclassOf<class ACEquipItem> TestWeaponClass;
	class ACEquipItem* TestWeapon;

	TSubclassOf<class UCPlayerHp> PlayerHpWidgetClass;
	class UCPlayerHp* PlayerHpWidget;

	class ACFieldItem* PickableActor;
	TArray<FCItemStruct> MyItems;
	int32 MaxItem = 15;

	// Weapons
};
