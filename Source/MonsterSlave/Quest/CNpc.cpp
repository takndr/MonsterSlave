#include "Quest/CNpc.h"

#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

#include "Component/CQuestComponent.h"

#include "Player/CPlayer.h"
#include "Widgets/CInteract.h"
#include "Quest/CQuestData.h"
#include "Widgets/Quest/CQuestMain.h"

#include "Global.h"

ACNpc::ACNpc()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere", RootComponent);
	CHelpers::CreateSceneComponent(this, &NiagaraComp, "NiagaraComp", GetMesh());
	CHelpers::CreateActorComponent(this, &QuestComp, "Quest");

	Sphere->SetSphereRadius(200.0f);

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);

	// SkeletalMesh Setting
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "/Game/NPC/_Asset/BattleWizardPolyart/Meshes/WizardSM");
	GetMesh()->SetSkeletalMesh(meshAsset);

	// NiagaraComp Setting
	NiagaraComp->SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));
	NiagaraComp->SetRelativeScale3D(FVector(2.0f));
	CHelpers::GetAsset(&AvailableQuest, "/Game/NPC/_Asset/Expressive_Head_VFX/Niagara/PS_State_Exclamation");
	CHelpers::GetAsset(&CompletedQuest, "/Game/NPC/_Asset/Expressive_Head_VFX/Niagara/PS_State_Interogation");

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
	CHelpers::GetClass(&QuestMainWidgetClass, "/Game/Widgets/Widget/Quest/WB_QuestMain");
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

	QuestMainWidget = CreateWidget<UCQuestMain>(GetWorld(), QuestMainWidgetClass);
}

void ACNpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (QuestComp->HasAvailableQuest())
	{
		NiagaraComp->SetAsset(AvailableQuest);
	}

	if (QuestComp->HasCompletedQuest())
	{
		NiagaraComp->SetAsset(CompletedQuest);
	}
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
	CheckNull(QuestMainWidget);
	QuestMainWidget->AddToViewport();
	QuestMainWidget->SetVisibility(ESlateVisibility::Visible);

	for (auto questData : QuestComp->GetQuestDatas())
	{
		QuestMainWidget->AddQuestList(questData);
	}

	FInputModeUIOnly inputMode;

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);

	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	for (auto quest : player->Quests)
	{
		if (quest->OnQuestCheck.IsBound())
		{
			quest->OnQuestCheck.Execute(this);
		}
	}
}