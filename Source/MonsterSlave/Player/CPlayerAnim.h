#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Items/ItemStruct.h"
#include "CPlayerAnim.generated.h"

UCLASS()
class MONSTERSLAVE_API UCPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Direction = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Pitch = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bAim = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		EWeaponType WeaponType;

private:
	class ACharacter* OwnerCharacter;
	class UCWeaponComponent* WeaponComponent;
};
