#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrow.generated.h"

UCLASS()
class MONSTERSLAVE_API ACArrow : public AActor
{
	GENERATED_BODY()
public:
	ACArrow();
protected:
	virtual void BeginPlay() override;
// ==================================================================
public:
	static ACArrow* Spawn(class UWorld* InWorld, class ACharacter* InOwner);
// ==================================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// ==================================================================

// ==================================================================
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
};
