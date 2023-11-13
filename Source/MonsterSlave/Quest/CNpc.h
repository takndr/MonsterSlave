#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CNpc.generated.h"

UCLASS()
class MONSTERSLAVE_API ACNpc : public ACharacter
{
	GENERATED_BODY()
public:
	ACNpc();
protected:
	virtual void BeginPlay() override;
//=============================================================================

//=============================================================================
private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnInteract();
//=============================================================================
private:
	class TSubclassOf<UUserWidget> InteractWidgetClass;
	class UCInteract* InteractWidget;

//=============================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UCQuestComponent* Quest;

};
