#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Items/ItemStruct.h"
#include "CPlayerState.generated.h"

UCLASS()
class MONSTERSLAVE_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ACPlayerState();
public:
	TArray<FCItemStruct> MyItems;

};
