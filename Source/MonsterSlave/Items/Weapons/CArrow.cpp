#include "Items/Weapons/CArrow.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Component/CWeaponComponent.h"

#include "Items/CItemData.h"
#include "Items/CEquipItem.h"
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
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	OwnerItem = weaponComp->GetCurrentWeapon()->GetEquipItem();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlashEffect, GetActorLocation(), GetActorRotation());
	
	SetLifeSpan(1.0f);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACArrow::OnOverlap);
}

void ACArrow::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 여러 조건 붙이고 통과하면 진행 -> 본인과 Owner 제외
	CheckTrue(OwnerCharacter == OtherActor);

	FVector impactNormal = SweepResult.ImpactNormal;
	FVector location = SweepResult.Location;
	FRotator rotator = UKismetMathLibrary::MakeRotFromX(impactNormal);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, location + impactNormal * 5, rotator);

	if (OwnerItem->ComboCount == 2)
	{
		OwnerItem->bNormal = false;
		OwnerItem->bKnockBack = true;
	}
	else
	{
		OwnerItem->bNormal = true;
		OwnerItem->bKnockBack = false;
	}

	// 데미지를 줄 경우는 적일 경우에만
	if (Cast<ACBoss>(OtherActor) != nullptr)
	{
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(Damage, damageEvent, OwnerCharacter->GetController(), OwnerItem);
	}
	
	if (Cast<ACDummyEnemy>(OtherActor) != nullptr)
	{
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(Damage, damageEvent, OwnerCharacter->GetController(), OwnerItem);
	}

	this->Destroy();
}

