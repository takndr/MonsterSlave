#include "Items/Weapons/CArrow.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Global.h"

ACArrow::ACArrow() {
	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &StaticMesh, "Mesh", Scene);
	CHelpers::CreateSceneComponent(this, &Capsule, "Collision", StaticMesh);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	UStaticMesh* staticMesh;
	CHelpers::GetAsset(&staticMesh, "StaticMesh'/Game/Items/Weapons/_Asset/Arrow/SM_Arrow.SM_Arrow'");
	StaticMesh->SetStaticMesh(staticMesh);
	//StaticMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	StaticMesh->SetCollisionProfileName("NoCollision");

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Projectile Setting
	Projectile->ProjectileGravityScale = 0.0f;
	//Projectile->InitialSpeed = 100.0f;
	//Projectile->MaxSpeed = 100.0f;
	Projectile->SetVelocityInLocalSpace(FVector(0.0f, 0.0f, 0.0f));
	SetActorScale3D(FVector(3.0f));
}

void ACArrow::BeginPlay() {
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACArrow::OnOverlap);
}

void ACArrow::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	//CheckTrue(GetOwner() == OtherActor);

	// TODO : �ٴ���Ʈ ���� �ȵǰ� HittedActors�� TArray�� �����Ͽ� ��������
	// ���� Collision�� ������ �ٸ� Actor�� HittedActors�迭�� ���� ��� return�Ͽ� �ڵ� �� ���� ���ϰ�
	if (HittedActors.Find(OtherActor) != -1) {
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : ������ �ٶ� ��������Ʈ�ؼ� actor���� �ٸ� ȿ�� �Ͼ���� �����ϸ� ������ �� ���⵵ ��
	// ������ ������ �ֱ�
	//FDamageEvent damageEvent;
	//InOtherCharacter->TakeDamage(Datas[ComboCount].Power, damageEvent, InAttacker->GetController(), InCauser);
}

ACArrow* ACArrow::Spawn(UWorld* InWorld, ACharacter* InOwner) {
	FActorSpawnParameters param;
	param.Owner = InOwner;
	//OwnerCharacter = InOwner;
	return InWorld->SpawnActor<ACArrow>(param);
}

// TODO :: �߻�� ������ ���� ������ ��Ȯ���� ����, ������ ĳ���Ͱ� ���� �ִ� ������ ������ �� ����
void ACArrow::ShootArrow() {
	//Capsule->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	Projectile->SetVelocityInLocalSpace(FVector(100.0f, 0.0f, 0.0f));
	//Projectile->Velocity = FVector(100.0f, 0.0f, 0.0f);
	SetLifeSpan(20.0f);
}