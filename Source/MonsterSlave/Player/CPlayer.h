#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Items/ItemStruct.h"
#include "CPlayer.generated.h"

DECLARE_DYNAMIC_DELEGATE(FInteractSignature);

UCLASS()
class MONSTERSLAVE_API ACPlayer : public ACharacter
{
	GENERATED_BODY()
public:
	ACPlayer();
protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
// ============================================================================
public:
	void AddItem(class UCItemData* InItem);
	void RemoveInventoryItem(class UCItemData* InItem);
	void ReplaceInventoryItem(class UCItemData* OldItem, class UCItemData* NewItem);
	void Dead();
	
	FORCEINLINE class UCInventory* GetInventory() {	return InventoryWidget;	}
	FORCEINLINE class UCPlayerStatus* GetPlayerStatus() { return StatusWidget; }
	FORCEINLINE class UCameraComponent* GetMeshCamera() { return MeshCamera; }
private:
	// Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnHorizontalLook(float Axis);
	void OnVerticalLook(float Axis);
	void OnZoom(float Axis);

	// Action Event
	void Inventory();
	void Attack();
	void Interact();
	void OnSwordWeapon();
	void OnBowWeapon();
	void FirstSkill();
	void SecondSkill();
	void OnStatus();
	void OnQuestLog();

	void Hitted(AActor* DamageCauser);

// ============================================================================
public:
	UFUNCTION(Exec)
		void TakeDamageTest();

	UFUNCTION(Exec)
		void IncreaseStatTest();
private:
	UFUNCTION()
		void EndDead();

	UFUNCTION()
		void SaveDatas();
// ===========================================================
protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* MeshCamera;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MeshSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* MinimapCamera;

	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* MinimapSpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UPaperSpriteComponent* MinimapSprite;

	UPROPERTY(VisibleDefaultsOnly)
		class UCPlayerStatusComponent* PlayerStatusComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* OptionComponent;

	

	UPROPERTY(VisibleDefaultsOnly)
		class UCQuestComponent* QuestComponent;
// ===========================================================
private:
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* DieMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* HitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* KnockbackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* PickupMontage;

// ===========================================================
public:
	FInteractSignature OnInteract;
	TArray<class UCItemData*> Items;
	TArray<class UCQuestData*> Quests;
	int32 MaxItem = 30;

private:
	class USkeletalMesh* PlayerBody;
	class ACPlayerHair* PlayerHair;
	
	TSubclassOf<class UCPlayerMain> PlayerMainWidgetClass;
	class UCPlayerMain* PlayerMainWidget;

	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	class UCInventory* InventoryWidget;

	TSubclassOf<class UCQuestMain> QuestMainWidgetClass;
	class UCQuestMain* QuestMainWidget;

	TSubclassOf<class UCPlayerStatus> StatusWidgetClass;
	class UCPlayerStatus* StatusWidget;

	TSubclassOf<class UCPlayerQuestLog> QuestLogWidgetClass;
	class UCPlayerQuestLog* QuestLogWidget;

	bool bKnockDown = false;
};
