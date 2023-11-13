#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Global.h"

// TODO7 : HittedActor를 OffCollision쪽에 초기화를 진행해두었는데, 이 위치가 맞는지 다시 한번 고심해서 재조정
ACEquipSword::ACEquipSword()
{
	WeaponType = EWeaponType::Sword;
	CHelpers::CreateSceneComponent(this, &Capsule, "Collision", StaticMesh);
}

void ACEquipSword::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACEquipSword::OnOverlap);
}

void ACEquipSword::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 여러 조건 붙이고 통과하면 진행 -> 본인과 Owner 제외
	CheckTrue(OtherActor == OwnerCharacter);
	
	if (HittedActors.Find(OtherActor) != -1)
	{
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : 데미지 줄때 델리게이트해서 actor마다 다른 효과 일어나도록 진행하면 괜찮을 것 같기도 함
	FDamageEvent damageEvent;
	damageEvent.DamageTypeClass;
	
	if (ComboCount == 2)
	{
		CLog::Print("KnockBack");
		bNormal = false;
		bKnockBack = true;
	}
	else
	{
		CLog::Print("Normal");
		bNormal = true;
		bKnockBack = false;
	}
	
	OtherActor->TakeDamage(30.0f, damageEvent, OwnerCharacter->GetController(), this);
}

void ACEquipSword::OnCollision()
{
	CheckNull(Capsule);

	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACEquipSword::OffCollision()
{
	CheckNull(Capsule);

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HittedActors.Empty();
	HittedActors.Shrink();
}
