#include "Items/Weapons/CArrow.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"

#include "Global.h"

ACArrow::ACArrow() {
	CHelpers::CreateSceneComponent(this, &Sphere, "Collision");
	CHelpers::CreateSceneComponent(this, &ProjectileEffect, "ProjectileEffect", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetSphereRadius(10.0f);

	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->InitialSpeed = ArrowSpeed;
	Projectile->MaxSpeed = 0.0f;
}

void ACArrow::BeginPlay() {
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlashEffect, GetActorLocation(), GetActorRotation());
	
	SetLifeSpan(1.0f);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACArrow::OnOverlap);
}

void ACArrow::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	CheckTrue(Owner == OtherActor);

	FVector impactNormal = SweepResult.ImpactNormal;
	FVector location = SweepResult.Location;
	FRotator rotator = UKismetMathLibrary::MakeRotFromX(impactNormal);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, location + impactNormal * 5, rotator);

	// �������� �� ���� ���� ��쿡��
	if (Cast<ACBoss>(OtherActor) != nullptr)
	{
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(Damage, damageEvent, Owner->GetController(), this);
	}
	
	if (Cast<ACDummyEnemy>(OtherActor) != nullptr)
	{
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(Damage, damageEvent, Owner->GetController(), this);
	}




	this->Destroy();
}

