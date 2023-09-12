#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CBossHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCBossHp : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealth(float currentHealth, float maxHealth);
	void UpdateName(FText InText);
protected:

private:

// ============================================================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* BossHp;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* BossName;

};
