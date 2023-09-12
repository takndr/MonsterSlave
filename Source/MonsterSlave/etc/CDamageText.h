#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDamageText.generated.h"

UCLASS()
class MONSTERSLAVE_API ACDamageText : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDamageText();
	//void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
// =================================================================
public:
	void SetDamageText(float InDamage);

// =================================================================

// =================================================================
private:
// =================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* DamageWidgetComp;
};
