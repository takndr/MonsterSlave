#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CPlayerMain.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerMain : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ==================================================================
public:
	void UpdateHealth();
// ==================================================================
protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetHealthRatio();

private:
	UFUNCTION()
		void OnWeaponChanged(EWeaponType InPrevType, EWeaponType InNewType);

	UFUNCTION()
		void OnFirstSkillCoolDown(float InCoolDown);

	UFUNCTION()
		void OffFirstSkillCoolDown();

	UFUNCTION()
		void OnSecondSkillCoolDown(float InCoolDown);

	UFUNCTION()
		void OffSecondSkillCoolDown();
// ==================================================================
private:
	class ACharacter* OwnerCharacter;

// ==================================================================
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* Health;
private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHP;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHP;
// ==================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UImage* WeaponImage;
// ==================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UImage* FirstSkillImage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* FirstSkillCoolDown;
// ==================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UImage* SecondSkillImage;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SecondSkillCoolDown;
};
