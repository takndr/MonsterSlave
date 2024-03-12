#pragma once

#include "CoreMinimal.h"
#include "Component/CStatusComponent.h"
#include "CPlayerStatusComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FHpStatSignature, float, InHPStat, float, InRemainStat);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FPowerStatSignature, float, InPowerStat, float, InRemainStat);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSpeedStatSignature, float, InSpeedStat, float, InRemainStat);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FDefenseStatSignature, float, InDefenseStat, float, InRemainStat);
DECLARE_DYNAMIC_DELEGATE_OneParam(FButtonAppearSignature, float, InRemainStat);
DECLARE_DYNAMIC_DELEGATE(FButtonDisappearSignature);
DECLARE_DYNAMIC_DELEGATE(FHealthTextSettingSignature);

UCLASS()
class MONSTERSLAVE_API UCPlayerStatusComponent : public UCStatusComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
// ============================================================================
public:
	FORCEINLINE float GetHpStat() { return HpStat; }
	FORCEINLINE float GetPowerStat() { return PowerStat; }
	FORCEINLINE float GetSpeedStat() { return SpeedStat; }
	FORCEINLINE float GetDefenseStat() { return DefenseStat; }
	FORCEINLINE float GetRemainStat() { return RemainStatusPoint; }

	void IncreaseRemainStat(float dx);		// Test¿ë
private:
	void DecreaseRemainStat(float dx);

	void SetHealth();
	void SetSpeed();
// ============================================================================
private:
	UFUNCTION()
		void SaveStatusDatas();

	UFUNCTION()
		void OnHP();

	UFUNCTION()
		void OnPower();

	UFUNCTION()
		void OnDefense();

	UFUNCTION()
		void OnSpeed();
// ============================================================================
public:
	FHpStatSignature OnHpStat;
	FPowerStatSignature OnPowerStat;
	FSpeedStatSignature OnSpeedStat;
	FDefenseStatSignature OnDefenseStat;

	FButtonAppearSignature OnButtonAppear;
	FButtonDisappearSignature OnButtonDisappear;

	FHealthTextSettingSignature OnHealthTextSetting;
// ============================================================================
private:
	UPROPERTY(EditDefaultsOnly)
		float HpStat = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		float PowerStat = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		float SpeedStat = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		float DefenseStat = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		float RemainStatusPoint = 5.0f;
};
