#include "Items/Weapons/CArrow.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Component/CWeaponComponent.h"
#include "Component/CPlayerStatusComponent.h"
#include "etc/CDamageText.h"

#include "Items/CItemData.h"
#include "Items/CEquipItem.h"
#include "Enemy/CBoss.h"
#include "Enemy/CDummyEnemy.h"

#include "Global.h"

ACArrow::ACArrow()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Collision");
	CHelpers::CreateSceneComponent(this, &ProjectileEffect, "ProjectileEffect", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Sphere->SetSphereRadius(10.0f);

	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->InitialSpeed = ArrowSpeed;
	Projectile->MaxSpeed = 0.0f;
}

void ACArrow::BeginPlay()
{
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
	CheckTrue(OwnerCharacter == OtherActor);
	CheckFalse(Cast<ACEnemy>(OtherActor) != nullptr);

	// 화살 이펙트 실행
	{
		FVector impactNormal = SweepResult.ImpactNormal;
		FVector location = SweepResult.Location;
		FRotator rotator = UKismetMathLibrary::MakeRotFromX(impactNormal);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, location + impactNormal * 5, rotator);
	}
	
	// 카메라 떨림 실행
	if (!!ShakeClass)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->StartCameraShake(ShakeClass);
	}

	// 데미지를 줄 경우는 적일 경우에만
	if (Cast<ACEnemy>(OtherActor) != nullptr)
	{
		// 데미지 계산
		UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
		CheckNull(statusComp);

		float temp = Damage + statusComp->GetPowerStat() * 10;
		int finDamage = UKismetMathLibrary::RandomFloatInRange(temp - temp / 10, temp + temp / 10);

		// 데미지 폰트
		FTransform damageTransform = GetActorTransform();
		ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(ACDamageText::StaticClass(), damageTransform);
		damageText->FinishSpawning(damageTransform);
		damageText->SetDamageText(Damage);

		// 데미지 계산 실행
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(finDamage, damageEvent, OwnerCharacter->GetController(), OwnerItem);
	}

	this->Destroy();
}

