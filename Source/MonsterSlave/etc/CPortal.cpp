#include "etc/CPortal.h"

#include "Components/BoxComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Component/CWeaponComponent.h"
#include "Component/CStatusComponent.h"

#include "Widgets/CInteract.h"
#include "Player/CPlayer.h"
#include "GameMode/CSaveGame.h"
#include "Items/CEquipItem.h"

#include "Global.h"

ACPortal::ACPortal()
{
	CHelpers::CreateSceneComponent(this, &Box, "Box", RootComponent);
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Box);

	Particle->SetRelativeLocation(FVector(0.0f, 0.0f, -150.0f));

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
}

void ACPortal::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPortal::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPortal::EndOverlap);

	CheckNull(PortalParticle);
	Particle->SetTemplate(PortalParticle);

	InteractWidget = CreateWidget<UCInteract>(GetWorld(), InteractWidgetClass);
	CheckNull(InteractWidget);

	InteractWidget->AddToViewport();
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	InteractWidget->SetInteractText("Portal");
}

void ACPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Visible);

	player->OnInteract.BindUFunction(this, "OnInteract");
}

void ACPortal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	player->OnInteract.Unbind();
}

void ACPortal::OnInteract()
{
	if (OnPortalSave.IsBound())
	{
		OnPortalSave.Broadcast();
	}

	FString map = "/Game/Maps/Tutorial/" + NextMap;
	UGameplayStatics::OpenLevel(GetWorld(), (FName)map);
	//controller->ClientTravel(map, ETravelType::TRAVEL_Absolute);
}
