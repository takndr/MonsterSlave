#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/ItemStruct.h"
#include "CItemData.generated.h"

UCLASS()
class MONSTERSLAVE_API UCItemData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Items")
		FCItemStruct Item;
};
