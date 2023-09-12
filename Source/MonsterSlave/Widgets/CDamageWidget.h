#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CDamageWidget.generated.h"

UCLASS()
class MONSTERSLAVE_API UCDamageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetDamageWidget(const FText& InText);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Damage;
};
