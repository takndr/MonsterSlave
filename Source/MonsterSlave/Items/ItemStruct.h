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

	// UI���� ������ ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Picture;

	// �������� �ƴ���? ���� �ʿ��Ѱ� �ͱ⵵ �ϰ�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isWeapon;
};