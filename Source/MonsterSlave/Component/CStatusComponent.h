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
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	FORCEINLINE float GetMaxHp() { return MaxHp; }
// =================================================================
public:	
	UFUNCTION(BlueprintCallable)
		void IncreaseHealth(float Dx);

	UFUNCTION(BlueprintCallable)
		void DecreaseHealth(float Dx);
// =================================================================
private:
	float CurrentHp;
// =================================================================
private:
	UPROPERTY(EditAnywhere, Category = "Status : Hp")
		float MaxHp = 100.0f;
};
