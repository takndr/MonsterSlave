#include "Enemy/CEnemy.h"

#include "Global.h"

ACEnemy::ACEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return DamageValue;
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

