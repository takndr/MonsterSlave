#include "Player/CPlayerHair.h"

#include "GameFramework/Character.h"

#include "Global.h"

ACPlayerHair::ACPlayerHair() {
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");
	CHelpers::GetAsset(&PlayerHair, "SkeletalMesh'/Game/Player/Character/Mesh/Modular_Mesh/Hair1/SK_STgirl_Hair1.SK_STgirl_Hair1'");
	Mesh->SetSkeletalMesh(PlayerHair);

}

void ACPlayerHair::BeginPlay() {
	Super::BeginPlay();
	
	Owner = Cast<ACharacter>(GetOwner());

	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HairSocket);
}

void ACPlayerHair::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

ACPlayerHair* ACPlayerHair::Spawn(UWorld* InWorld, ACharacter* InOwner) {
	FActorSpawnParameters params;
	params.Owner = InOwner;

	return InWorld->SpawnActor<ACPlayerHair>(params);
}

