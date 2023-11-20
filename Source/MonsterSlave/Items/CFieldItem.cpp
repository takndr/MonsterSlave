#include "CFieldItem.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMesh.h"
#include "PaperSpriteComponent.h"

#include "Player/CPlayer.h"
#include "Widgets/CInteract.h"
#include "Component/CStatusComponent.h"
#include "Items/CItemData.h"

#include "Global.h"

ACFieldItem::ACFieldItem() 
{
	// Component Setting
	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &StaticMesh, "StaticMesh", Scene);
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", StaticMesh);
	CHelpers::CreateSceneComponent(this, &MinimapSprite, "Sprite", Sphere);

	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Sphere Collision Setting
	Sphere->SetSphereRadius(80.0f);

	// MinimapSprite Setting
	MinimapSprite->SetGenerateOverlapEvents(false);
	MinimapSprite->SetCollisionProfileName(TEXT("NoCollision"));

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
}

void ACFieldItem::BeginPlay() 
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACFieldItem::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ACFieldItem::EndOverlap);

	InteractWidget = CreateWidget<UCInteract>(GetWorld(), InteractWidgetClass);
	CheckNull(InteractWidget);

	InteractWidget->AddToViewport();
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	InteractWidget->SetInteractText(ItemDescription->Item.Interact);
}

void ACFieldItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Visible);

	player->OnInteract.BindUFunction(this, "OnInteract");
}

void ACFieldItem::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	player->OnInteract.Unbind();
}

void ACFieldItem::OnInteract()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckNull(player);

	if (player->Items.Num() == player->MaxItem)
	{
		CLog::Log("Not Enough Inventory...");
		return;
	}

	player->AddItem(ItemDescription);

	this->Destroy();
}
