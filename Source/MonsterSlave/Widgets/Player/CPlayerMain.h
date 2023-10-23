#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerMain.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerMain : public UUserWidget
{
	GENERATED_BODY()
// ==================================================================
public:
	void UpdateHealth();
// ==================================================================
protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetHealthRatio();
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
};
