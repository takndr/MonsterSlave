#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBossHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCBossHp : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHealth(float currentHealth, float maxHealth);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateBossName(const FText& InText);
protected:

private:

// ============================================================

public:

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* BossHp;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* BossName;

private:

};
