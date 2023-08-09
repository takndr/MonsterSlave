#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CItemDescription.generated.h"

UCLASS()
class MONSTERSLAVE_API UCItemDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:


// =========================================================

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemImage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemDescription;

};
