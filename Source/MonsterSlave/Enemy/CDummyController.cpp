#include "Enemy/CDummyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Component/CBehaviorComponent.h"
#include "Enemy/CDummyEnemy.h"
#include "Player/CPlayer.h"

#include "Global.h"

ACDummyController::ACDummyController()
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

void ACDummyController::BeginPlay()
{
	Super::BeginPlay();
}

void ACDummyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDebugMode);

	FVector center = PossessedDummy->GetActorLocation();

	DrawDebugSphere(GetWorld(), center, SightPerception->SightRadius, 30, FColor::Green);
	DrawDebugSphere(GetWorld(), center, BehaviorRange, 30, FColor::Red);
}

void ACDummyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedDummy = Cast<ACDummyEnemy>(InPawn);

	UBehaviorTree* behaviorTree = PossessedDummy->GetBehaviorTree();
	CheckNull(behaviorTree);

	UseBlackboard(behaviorTree->GetBlackboardAsset(), Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(behaviorTree);

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACDummyController::OnPerceptionUpdated);
}

void ACDummyController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}

void ACDummyController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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