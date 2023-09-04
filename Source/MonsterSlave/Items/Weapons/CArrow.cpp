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
	// 여러 조건 붙이고 통과하면 진행 -> 본인과 Owner 제외
	//CheckTrue(GetOwner() == OtherActor);
}

ACArrow* ACArrow::Spawn(UWorld* InWorld, ACharacter* InOwner) {
	FActorSpawnParameters param;
	param.Owner = InOwner;
	//OwnerCharacter = InOwner;
	return InWorld->SpawnActor<ACArrow>(param);
}

// TODO :: 발사는 되지만 아직 방향이 정확하지 않음, 방향은 캐릭터가 보고 있는 쪽으로 진행을 할 예정
void ACArrow::ShootArrow() {
	//Capsule->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	Projectile->SetVelocityInLocalSpace(FVector(100.0f, 0.0f, 0.0f));
	//Projectile->Velocity = FVector(100.0f, 0.0f, 0.0f);
	SetLifeSpan(20.0f);
}