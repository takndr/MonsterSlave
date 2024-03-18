#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CIKComponent.generated.h"

USTRUCT(BlueprintType)
struct FIKData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftFootDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightFootDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator LeftFootRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FRotator RightFootRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCIKComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCIKComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
// ==================================================================
public:
	FORCEINLINE const FIKData& GetData() { return Data; }

private:
	void Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation);
// ==================================================================

// ==================================================================
private:
	FIKData Data;
	class ACharacter* OwnerCharacter;
// ==================================================================
protected:
	UPROPERTY(EditAnywhere, Category = "IK")
		FName LeftFootSocket = "Foot_L";

	UPROPERTY(EditAnywhere, Category = "IK")
		FName RightFootSocket = "Foot_R";

	UPROPERTY(EditAnywhere, Category = "IK")
		float Extension = 55.0f;

	UPROPERTY(EditAnywhere, Category = "IK")
		float AdjustHeight = 5.0f;

	UPROPERTY(EditAnywhere, Category = "IK")
		float InterSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "IK")
		TEnumAsByte<EDrawDebugTrace::Type> DebugTrace = EDrawDebugTrace::ForDuration;
		
};
