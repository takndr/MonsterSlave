#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipItem.generated.h"

UCLASS()
class MONSTERSLAVE_API ACEquipItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// ===================================================

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* SkeletalMesh;


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;


};
