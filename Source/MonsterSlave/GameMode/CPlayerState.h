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
	//UPROPERTY(Replicated)
	//	class UCWeaponComponent* WeaponComponent;

	//UPROPERTY(Replicated)
	//	class UCStatusComponent* StatusComponent;

	//UPROPERTY(Replicated)
	//	class UCStateComponent* StateComponent;

	//UPROPERTY(Replicated)
	//	TArray<FCItemStruct> MyItems;

	float Heatlh;
};
