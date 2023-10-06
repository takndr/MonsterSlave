#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBossBreath.generated.h"

UCLASS()
class MONSTERSLAVE_API ACBossBreath : public AActor
{
	GENERATED_BODY()
public:	
	ACBossBreath();
protected:
	virtual void BeginPlay() override;
// ==================================================================
private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
// ==================================================================
private:
	class UParticleSystem* BreathParticle;
// ==================================================================
private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UCapsuleComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;
};
