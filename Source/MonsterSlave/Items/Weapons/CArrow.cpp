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
	StaticMesh->SetGenerateOverlapEvents(false);
	StaticMesh->SetCollisionProfileName("NoCollision");

	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Projectile->ProjectileGravityScale = 0.0f;
	Projectile->InitialSpeed = 200.0f;
	Projectile->MaxSpeed = 200.0f;
	Projectile->bAutoActivate = false;
	Projectile->bInitialVelocityInLocalSpace = false;

}

void ACArrow::BeginPlay() {
	Super::BeginPlay();
	Owner = Cast<ACharacter>(GetOwner());
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ACArrow::OnOverlap);
}

void ACArrow::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// ���� ���� ���̰� ����ϸ� ���� -> ���ΰ� Owner ����
	CheckTrue(Owner == OtherActor);

	if (HittedActors.Find(OtherActor) != -1) {
		return;
	}
	HittedActors.AddUnique(OtherActor);

	// TODO : ������ �ٶ� ��������Ʈ�ؼ� actor���� �ٸ� ȿ�� �Ͼ���� �����ϸ� ������ �� ���⵵ ��
	FDamageEvent damageEvent;
	OtherActor->TakeDamage(10.0f, damageEvent, Owner->GetController(), this);

	// TODO : Damage Effect


	// TODO : Damage Widget
}

// TODO :: �߻�� ������ ���� ������ ��Ȯ���� ����, ������ ĳ���Ͱ� ���� �ִ� ������ ������ �� ����, ���� �Ϻ��� �������� ����
void ACArrow::ShootArrow() {
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	FVector vector = Owner->GetControlRotation().Vector();
	Projectile->Velocity = vector * Projectile->InitialSpeed;
	CLog::Log(Projectile->Velocity);

	Projectile->Activate(true);
	SetLifeSpan(1.0f);
}