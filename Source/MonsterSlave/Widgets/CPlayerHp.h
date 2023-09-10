#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerHp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHealth(float CurrentHp, float MaxHp);

// ======================================================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* PlayerHpBar;
};
