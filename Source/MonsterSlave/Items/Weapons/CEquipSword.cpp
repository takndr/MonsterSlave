#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"

#include "Global.h"

// TODO7 : HittedActor�� OffCollision�ʿ� �ʱ�ȭ�� �����صξ��µ�, �� ��ġ�� �´��� �ٽ� �ѹ� ����ؼ� ������
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
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	CheckTrue(OtherActor == OwnerCharacter);
	
	if (HittedActors.Find(OtherActor) != -1)
	{
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : ������ �ٶ� ��������Ʈ�ؼ� actor���� �ٸ� ȿ�� �Ͼ���� �����ϸ� ������ �� ���⵵ ��
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
