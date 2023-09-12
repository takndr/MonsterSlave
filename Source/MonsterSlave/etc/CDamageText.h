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
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
// =================================================================
public:
	void SetDamageText(float InDamage);

// =================================================================
// =================================================================
// =================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
};
