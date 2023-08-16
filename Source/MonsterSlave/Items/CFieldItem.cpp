#include "CFieldItem.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMesh.h"
#include "PaperSpriteComponent.h"

#include "Player/CPlayer.h"
#include "Widgets/CInteract.h"
#include "Component/CStatusComponent.h"

#include "Global.h"

ACFieldItem::ACFieldItem() {
	PrimaryActorTick.bCanEverTick = true;

	// Component Setting
	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &SkeletalMesh, "SkeletalMesh", Scene);
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", SkeletalMesh);
	CHelpers::CreateSceneComponent(this, &MinimapSprite, "Sprite", Sphere);

	// Sphere Collision Setting
	Sphere->SetSphereRadius(80.0f);

	// MinimapSprite Setting
	MinimapSprite->SetGenerateOverlapEvents(false);
	MinimapSprite->SetCollisionProfileName(TEXT("NoCollision"));

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
}

void ACFieldItem::BeginPlay() {
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACFieldItem::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ACFieldItem::EndOverlap);

	InteractWidget = CreateWidget<UCInteract>(GetWorld(), InteractWidgetClass);
	CheckNull(InteractWidget);

	InteractWidget->AddToViewport();
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	InteractWidget->SetInteractText(ItemDescription.Interact);

	CLog::Log("Item : " + ItemDescription.Name + ", Index : " + FString::FromInt(ItemDescription.GetIndex()));
}

void ACFieldItem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACFieldItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Visible);
	player->bCanPickUp = true;
}

void ACFieldItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);
	player->bCanPickUp = false;
}

