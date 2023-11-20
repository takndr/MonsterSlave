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
	FORCEINLINE class ACEquipItem* GetEquipItem() { return EquipItem; }
	void SpawnEquipItem(UWorld* InWorld, class ACharacter* OwnerCharacter);
// ==================================================================
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Items")
		FCItemStruct Item;
// ==================================================================
private:
	class ACEquipItem* EquipItem;
};
