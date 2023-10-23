#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotifyUnEquipped.generated.h"

UCLASS()
class MONSTERSLAVE_API UCAnimNotifyUnEquipped : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
