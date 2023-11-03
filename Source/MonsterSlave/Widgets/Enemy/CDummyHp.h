#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDummyHp.generated.h"

UCLASS()
class MONSTERSLAVE_API UCDummyHp : public UUserWidget
{
	GENERATED_BODY()
// ==================================================================
public:	
	void UpdateHealth(float CurrentHp, float MaxHp);
// ==================================================================
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* Health;

	UPROPERTY(BlueprintReadOnly)
		float HpRatio;
};
