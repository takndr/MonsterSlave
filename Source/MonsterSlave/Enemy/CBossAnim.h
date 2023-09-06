#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CBossAnim.generated.h"

UCLASS()
class MONSTERSLAVE_API UCBossAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bFly;

private:
	class ACharacter* OwnerCharacter;
	
};
