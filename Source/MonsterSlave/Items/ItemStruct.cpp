#include "ItemStruct.h"

#include "Global.h"

AItemStruct::AItemStruct()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItemStruct::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemStruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void FCItemStruct::Init() {
	int32 i;
	while (1) {
		i = UKismetMathLibrary::RandomIntegerInRange(1, 65532);
		if (ItemIndexes.Find(i) == INDEX_NONE) {
			ItemIndexes.Add(i);
			Index = i;
			break;
		}
	}
}
