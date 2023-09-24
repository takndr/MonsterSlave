#include "Enemy/CBossController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Component/CBehaviorComponent.h"
#include "Player/CPlayer.h"
#include "Enemy/CBoss.h"

#include "Global.h"

ACBossController::ACBossController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent(this, &Perception, "Perception");
	CHelpers::CreateActorComponent(this, &Behavior, "Behavior");

	SightPerception = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");

	SightPerception->SightRadius = 1000.0f;
	SightPerception->LoseSightRadius = 1000.0f;
	SightPerception->PeripheralVisionAngleDegrees = 180.0f;
	SightPerception->SetMaxAge(2.0f);
	SightPerception->DetectionByAffiliation.bDetectEnemies = false;
	SightPerception->DetectionByAffiliation.bDetectFriendlies = false;
	SightPerception->DetectionByAffiliation.bDetectNeutrals = false;
	
	Perception->ConfigureSense(*SightPerception);
	Perception->SetDominantSense(SightPerception->GetClass());
}

void ACBossController::BeginPlay()
{
	Super::BeginPlay();
}

void ACBossController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDebugMode);
}

void ACBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedBoss = Cast<ACBoss>(InPawn);

	UBehaviorTree* behaviorTree = PossessedBoss->GetBehaviorTree();
	CheckNull(behaviorTree);

	UseBlackboard(behaviorTree->GetBlackboardAsset(), Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(behaviorTree);

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACBossController::OnPerceptionUpdated);
}

void ACBossController::OnUnPossess()
{
	Super::OnUnPossess();
	
	Perception->OnPerceptionUpdated.Clear();
}

void ACBossController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACPlayer* player = nullptr;
	for (const auto& actor : actors)
	{
		player = Cast<ACPlayer>(actor);
		if (!!player)
			break;
	}

	Blackboard->SetValueAsObject("PlayerKey", player);
}