#include "etc/CBossBreath.h"

#include "Gameframework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"

#include "Global.h"

ACBossBreath::ACBossBreath()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Collision, "Collision", Root);
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Root);
	
	CHelpers::GetAsset(&BreathParticle, "/Game/Boss/Breath/Particles/Fire/P_Flamethrower");
	Particle->SetTemplate(BreathParticle);
	Particle->bAutoActivate = false;

	Collision->SetCapsuleRadius(100.0f);
	Collision->SetCapsuleHalfHeight(900.0f);
	Collision->SetRelativeLocation(FVector(0.0f, 0.0f, 900.0f));
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBossBreath::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACBossBreath::OnBeginOverlap);
}

void ACBossBreath::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	CheckTrue(OtherActor == this);
	CheckTrue(OtherActor == Owner);

	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	ACBoss* boss = Cast<ACBoss>(Owner);
	CheckNull(boss);

	if (boss->HittedCharacters.Find(player) != -1) {
		return;
	}
	boss->HittedCharacters.AddUnique(player);

	CLog::Print("Breath Overlap");
}

void ACBossBreath::SetActivate(bool InActive)
{
	Particle->SetActive(InActive);
}

void ACBossBreath::OnCollision()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACBossBreath::OffCollision()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


