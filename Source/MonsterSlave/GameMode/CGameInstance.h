#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameSaveSignature);

UCLASS()
class MONSTERSLAVE_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Shutdown() override;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FGameSaveSignature OnGameSave;
};
