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

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void IncreaseHealth(float Dx);

	UFUNCTION(BlueprintCallable)
		void DecreaseHealth(float Dx);



// =================================================================

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status : Hp")
		float MaxHp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status : Hp")
		float CurrentHp;

protected:

private:

};
