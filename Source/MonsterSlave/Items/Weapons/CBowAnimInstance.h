#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CBowAnimInstance.generated.h"

UCLASS()
class MONSTERSLAVE_API UCBowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
	void SetOwnerCharacter(class ACharacter* InCharacter) { OwnerCharacter = InCharacter; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bAim = false;

private:
	class ACharacter* OwnerCharacter;
};
