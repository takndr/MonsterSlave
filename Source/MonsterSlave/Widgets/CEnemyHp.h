#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CEnemyHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCEnemyHp : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHealth(float currentHealth, float maxHealth);

protected:
	virtual bool Initialize() override;

private:

	// ==============================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* EnemyHp;
};
