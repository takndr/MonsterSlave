#include "Player/Skill/CArrowRain.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"

#include "Items/Weapons/CArrow.h"

#include "Global.h"

ACArrowRain::ACArrowRain()
{
	CHelpers::GetClass(&ArrowClass, "/Game/Items/Weapons/Arrow/BP_Arrow");
}

void ACArrowRain::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);
	UNavigationSystemV1* navSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	CheckNull(navSystem);

	for (uint8 i = 0; i < 10; i++)
	{
		FNavLocation randomLocation;
		navSystem->GetRandomReachablePointInRadius(GetActorLocation(), ArrowCrowded, randomLocation);

		FVector arrowLocation = FVector(randomLocation.Location.X, randomLocation.Location.Y, randomLocation.Location.Z + 500);
		FTransform transform;
		transform.SetLocation(arrowLocation);
		transform.SetRotation((FQuat)FRotator(-90, 0, 0));
		
		FActorSpawnParameters spawnParameter;
		spawnParameter.Owner = OwnerCharacter;

		GetWorld()->SpawnActor<ACArrow>(ArrowClass, transform, spawnParameter);
		
	}

	SetLifeSpan(3.0f);
}


