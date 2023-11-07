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

// ==================================================================
private:
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// ==================================================================
public:
	class ACharacter* Owner;

private:
// ==================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UNiagaraComponent* ProjectileEffect;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(EditDefaultsOnly)
		class UNiagaraSystem* FlashEffect;

	UPROPERTY(EditDefaultsOnly)
		class UNiagaraSystem* HitEffect;

	UPROPERTY(EditDefaultsOnly)
		float ArrowSpeed = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
		float Damage = 20.0f;
};
