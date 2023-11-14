#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"

#include "ItemStruct.generated.h"

static TArray<int32> ItemIndexes;

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	Food,
	Other,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed,
	Sword,
	Bow,
	Max
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
struct FCItemStruct : public FTableRowBase {
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetIndex() const { return Index; }
	void Init();

public:

// ==============================================

public:
	// 아이템 이름
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name = "NULL";

	// 아이템 설명
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Description;

	// 상호작용 멘트
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Interact;

	// 아이템 타입
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EItemType ItemType;

	// 무기일 시, 무기 타입
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EWeaponType WeaponType;

	// 장착 장비 클래스 래퍼런스
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ACEquipItem> EquipWeaponClass;

	// 필드 장비 클래스 래퍼런스
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ACFieldItem> FieldWeaponClass;

	// UI에서 보여줄 사진
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Picture;

	// 무기인지 아닌지? 굳이 필요한가 싶기도 하고
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isWeapon;

private:
	int32 Index = 0;
};

FORCEINLINE bool operator==(const FCItemStruct& Lhs, const FCItemStruct& Rhs) {
	return Lhs.GetIndex() == Rhs.GetIndex();
}

FORCEINLINE bool operator==(const FCItemStruct* Lhs, const FCItemStruct& Rhs) {
	return Lhs->GetIndex() == Rhs.GetIndex();
}