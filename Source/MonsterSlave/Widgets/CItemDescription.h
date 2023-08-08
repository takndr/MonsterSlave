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

private:
	UPROPERTY(meta = (BindWidget))
		class UImage* ItemImage;
	
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemType;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemDescription;

};
