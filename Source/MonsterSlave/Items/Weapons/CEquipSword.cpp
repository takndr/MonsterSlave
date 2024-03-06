#include "Items/Weapons/CEquipSword.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

#include "Player/CPlayer.h"
#include "Component/CStateComponent.h"
#include "Component/CPlayerStatusComponent.h"
#include "etc/CDamageText.h"

#include "Enemy/CEnemy.h"

#include "Global.h"

// TODO7 : HittedActor�� OffCollision�ʿ� �ʱ�ȭ�� �����صξ��µ�, �� ��ġ�� �´��� �ٽ� �ѹ� ����ؼ� ������
ACEquipSword::ACEquipSword()
{
	WeaponType = EWeaponType::Sword;
	CHelpers::CreateSceneComponent(this, &Capsule, "Collision", StaticMesh);
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	
	CLog::Log("Combo : " + FString::FromInt(ComboCount));

	if (HittedActors.Find(OtherActor) != -1)
	{
		return;
	}
	HittedActors.AddUnique(OtherActor);

	if (!!ShakeClass)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->StartCameraShake(ShakeClass);
	}

	// �������� �� ���� ���� ��쿡��
	if (Cast<ACEnemy>(OtherActor) != nullptr)
	{
		// ������ ���
		UCPlayerStatusComponent* statusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
		CheckNull(statusComp);

		float temp = Damage + statusComp->GetPowerStat() * 10;
		int finDamage = UKismetMathLibrary::RandomFloatInRange(temp - temp / 10, temp + temp / 10);

		// ������ ��Ʈ
		FTransform damageTransform = GetActorTransform();
		ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(ACDamageText::StaticClass(), damageTransform);
		damageText->FinishSpawning(damageTransform);
		damageText->SetDamageText(finDamage);

		// ������ ��� ����
		FDamageEvent damageEvent;
		OtherActor->TakeDamage(finDamage, damageEvent, OwnerCharacter->GetController(), this);
	}
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

	bNormal = false;
	bKnockBack = false;
}
