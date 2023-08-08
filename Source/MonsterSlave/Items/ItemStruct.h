#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"

#include "ItemStruct.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Food,
	Other,
};

UCLASS()
class MONSTERSLAVE_API AItemStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemStruct();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(Atomic, BlueprintType)
struct FCItemStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 아이템 이름
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	// 아이템 설명
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Description;

	// 상호작용 멘트
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Interact;

	// 아이템 타입
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EItemType ItemType;

	// UI에서 보여줄 사진
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Picture;

	// 무기인지 아닌지? 굳이 필요한가 싶기도 하고
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isWeapon;
};