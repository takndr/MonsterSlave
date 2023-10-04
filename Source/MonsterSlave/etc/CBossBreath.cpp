#include "etc/CBossBreath.h"

#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Global.h"

ACBossBreath::ACBossBreath()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACBossBreath::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACBossBreath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

