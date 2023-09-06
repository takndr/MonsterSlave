#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAVE_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();
protected:
	virtual void BeginPlay() override;

// =================================================================
public:
	FORCEINLINE bool IsDead() { return CurrentHp <= 0; }
// =================================================================
public:	
	UFUNCTION(BlueprintCallable)
		void IncreaseHealth(float Dx);

	UFUNCTION(BlueprintCallable)
		void DecreaseHealth(float Dx);
// =================================================================
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status : Hp")
		float MaxHp = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status : Hp")
		float CurrentHp;

protected:

private:

};
