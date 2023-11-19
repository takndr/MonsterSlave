#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Items/ItemStruct.h"
#include "CSaveGame.generated.h"

UCLASS()
class MONSTERSLAVE_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly)
		FCItemStruct SwordItem;

	UPROPERTY(VisibleDefaultsOnly)
		FCItemStruct BowItem;

	UPROPERTY(VisibleDefaultsOnly)
		EWeaponType WeaponType;

	UPROPERTY(VisibleDefaultsOnly)
		float MaxHp;

	UPROPERTY(VisibleDefaultsOnly)
		float CurrentHp;

	UPROPERTY(VisibleDefaultsOnly)
		float MoveSpeed;

	UPROPERTY(VisibleDefaultsOnly)
		TArray<FCItemStruct> Items;

	UPROPERTY(VisibleDefaultsOnly)
		TArray<class UCItemData*> Item;

	//UPROPERTY(VisibleDefaultsOnly)
		
};
