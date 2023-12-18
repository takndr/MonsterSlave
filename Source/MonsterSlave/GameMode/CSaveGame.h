#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Quest/CQuestData.h"
#include "Items/ItemStruct.h"
#include "CSaveGame.generated.h"

UCLASS()
class MONSTERSLAVE_API UCSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly)
		FName CurrentLevelName;

	UPROPERTY(VisibleDefaultsOnly)
		FVector LastPlayerLocation;
		
	UPROPERTY(VisibleDefaultsOnly)
		class UCItemData* SwordItem;

	UPROPERTY(VisibleDefaultsOnly)
		class UCItemData* BowItem;

	UPROPERTY(VisibleDefaultsOnly)
		EWeaponType WeaponType;

	UPROPERTY(VisibleDefaultsOnly)
		float MaxHp;

	UPROPERTY(VisibleDefaultsOnly)
		float CurrentHp;

	UPROPERTY(VisibleDefaultsOnly)
		float MoveSpeed;

	UPROPERTY(VisibleDefaultsOnly)
		float HpStat;

	UPROPERTY(VisibleDefaultsOnly)
		float PowerStat;

	UPROPERTY(VisibleDefaultsOnly)
		float SpeedStat;

	UPROPERTY(VisibleDefaultsOnly)
		float DefenseStat;

	UPROPERTY(VisibleDefaultsOnly)
		float RemainStatPoint;

	UPROPERTY(VisibleDefaultsOnly)
		TArray<FQuest> AllQuests;

	UPROPERTY(VisibleDefaultsOnly)
		TArray<class UCItemData*> PlayerItems;

	UPROPERTY(VisibleDefaultsOnly)
		TArray<class UCQuestData*> PlayerQuests;
};
