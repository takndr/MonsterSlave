#include "Quest/CNpc.h"

#include "Components/SphereComponent.h"

#include "Component/CQuestComponent.h"

#include "Player/CPlayer.h"
#include "Widgets/CInteract.h"

#include "Global.h"

ACNpc::ACNpc()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", RootComponent);
	CHelpers::CreateActorComponent(this, &Quest, "Quest");

	Sphere->SetSphereRadius(200.0f);

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);

	// SkeletalMesh Setting
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/NPC/_Asset/BattleWizardPolyart/Meshes/WizardSM");
	GetMesh()->SetSkeletalMesh(meshAsset);

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
}

void ACNpc::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACNpc::BeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ACNpc::EndOverlap);

	InteractWidget = CreateWidget<UCInteract>(GetWorld(), InteractWidgetClass);
	CheckNull(InteractWidget);

	InteractWidget->AddToViewport();
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	InteractWidget->SetInteractText("Quest");
}

void ACNpc::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Visible);

	player->OnInteract.BindUFunction(this, "OnInteract");
}

void ACNpc::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	player->OnInteract.Unbind();
}

void ACNpc::OnInteract()
{
	CLog::Print("Check Quest");

	//CheckNull(QuestMainWidget);
}