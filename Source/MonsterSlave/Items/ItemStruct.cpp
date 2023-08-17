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

FCItemStruct::FCItemStruct() {
	/*int32 i;
	while (1) {
		i = UKismetMathLibrary::RandomIntegerInRange(0, 65532);
		if (ItemIndexes.Find(i) == INDEX_NONE) {
			CLog::Log(i);
			ItemIndexes.Add(i);
			Index = i;
			break;
		}
	}*/

}

void FCItemStruct::Init()
{
	PrintLine();

	int32 i;
	while (1) {
		i = UKismetMathLibrary::RandomIntegerInRange(0, 65532);
		if (ItemIndexes.Find(i) == INDEX_NONE) {
			CLog::Log(i);
			ItemIndexes.Add(i);
			Index = i;
			break;
		}
	}
}

bool FCItemStruct::operator==(const FCItemStruct& Other) {
	if (Index == Other.GetIndex()) {
		return true;
	}
	return false;
}
