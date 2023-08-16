#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/ItemStruct.h"
#include "CItemDescription.generated.h"

UCLASS()
class MONSTERSLAVE_API UCItemDescription : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SettingDescription(FCItemStruct item);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SettingDescriptionTest(FCItemStruct item);

// =========================================================

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* ItemImage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemType;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemDescription;

};
