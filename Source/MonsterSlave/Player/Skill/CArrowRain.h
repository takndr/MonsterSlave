#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrowRain.generated.h"

UCLASS()
class MONSTERSLAVE_API ACArrowRain : public AActor
{
	GENERATED_BODY()
public:	
	ACArrowRain();
protected:
	virtual void BeginPlay() override;
private:
	class ACharacter* OwnerCharacter;
	TSubclassOf<class ACArrow> ArrowClass;
private:
	UPROPERTY(EditDefaultsOnly)
		float ArrowCrowded = 400.0f;
};
