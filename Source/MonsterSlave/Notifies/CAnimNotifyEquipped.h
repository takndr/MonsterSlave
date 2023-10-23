#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotifyEquipped.generated.h"

UCLASS()
class MONSTERSLAVE_API UCAnimNotifyEquipped : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
