#include "etc/CBossBreath.h"

#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Global.h"

ACBossBreath::ACBossBreath()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Collision, "Collision", Root);
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Root);
	
	CHelpers::GetAsset(&BreathParticle, "/Game/Boss/Breath/Particles/Fire/P_Flamethrower");
	Particle->SetTemplate(BreathParticle);

	Collision->SetCapsuleRadius(100.0f);
	Collision->SetCapsuleHalfHeight(1200.0f);
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, 1200.0f));

}

void ACBossBreath::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACBossBreath::OnBeginOverlap);
}

void ACBossBreath::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Print("Breath Overlap");
}


