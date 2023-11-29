#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerStatus.generated.h"

DECLARE_DYNAMIC_DELEGATE(FIncreaseHpStatSignature);
DECLARE_DYNAMIC_DELEGATE(FIncreasePowerStatSignature);
DECLARE_DYNAMIC_DELEGATE(FIncreaseSpeedStatSignature);
DECLARE_DYNAMIC_DELEGATE(FIncreaseDefenseStatSignature);

UCLASS()
class MONSTERSLAVE_API UCPlayerStatus : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
// ============================================================================
public:
	bool IsOpened() { return bOpened; }
	void Attach();
	void Detach();
// ============================================================================
private:
	UFUNCTION()
		void OnClickHPButton();

	UFUNCTION()
		void OnClickPowerButton();

	UFUNCTION()
		void OnClickSpeedButton();

	UFUNCTION()
		void OnClickDefenseButton();

	UFUNCTION()
		void SetHpStatText(float InStat, float InRemainStat);

	UFUNCTION()
		void SetPowerStatText(float InStat, float InRemainStat);

	UFUNCTION()
		void SetDefenseStatText(float InStat, float InRemainStat);

	UFUNCTION()
		void SetSpeedStatText(float InStat, float InRemainStat);

	UFUNCTION()
		void AppearIncreaseButton(float InStat);

	UFUNCTION()
		void DisappearIncreaseButton();

// ============================================================================
public:
	// 델리게이트들
	FIncreaseHpStatSignature OnIncreaseHpStat;
	FIncreasePowerStatSignature OnIncreasePowerStat;
	FIncreaseSpeedStatSignature OnIncreaseSpeedStat;
	FIncreaseDefenseStatSignature OnIncreaseDefenseStat;
private:
	class ACharacter* OwnerCharacter;
	bool bOpened = false;
// ============================================================================
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* HPButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* PowerButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* SpeedButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* DefenseButton;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HPStat;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PowerStat;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SpeedStat;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* DefenseStat;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* StatusPointBox;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* StatusPointText;

	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* SwordEquipment;

	UPROPERTY(meta = (BindWidget))
		class UCEquipSlot* BowEquipment;
};
