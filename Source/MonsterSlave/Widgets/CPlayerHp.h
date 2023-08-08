#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerHp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHealth(float MaxHp, float CurrentHp);

// ======================================================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* PlayerHpBar;
};
