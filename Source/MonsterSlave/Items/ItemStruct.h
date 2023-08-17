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
	Sword,
	Bow,
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
	FCItemStruct();

	FORCEINLINE uint32 GetIndex() const { return Index; }
	void Init();

public:
	bool operator==(const FCItemStruct& Other);

// ==============================================

public:
	// ������ �̸�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	// ������ ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Description;

	// ��ȣ�ۿ� ��Ʈ
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Interact;

	// ������ Ÿ��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EItemType ItemType;

	// ������ ��, ���� Ÿ��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EWeaponType WeaponType;

	// Ŭ���� ���۷���
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class ACEquipItem> EquipWeaponClass;

	// UI���� ������ ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Picture;

	// �������� �ƴ���? ���� �ʿ��Ѱ� �ͱ⵵ �ϰ�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isWeapon;

private:
	int32 Index;
};