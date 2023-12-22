#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPortal.generated.h"

UCLASS()
class MONSTERSLAVE_API ACPortal : public AActor
{
	GENERATED_BODY()
public:	
	ACPortal();
protected:
	virtual void BeginPlay() override;
//=============================================================================
public:
	FORCEINLINE bool IsActive() { return bActive; }
	FORCEINLINE void SetActive(bool InActive) { bActive = InActive; }
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
	bool bActive = false;
//=============================================================================
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

public:
	UPROPERTY(EditAnywhere)
		TSoftObjectPtr<UWorld> NextLevel;

	UPROPERTY(EditAnywhere)
		FString ObjectPlayerStartOption;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* PortalParticle;
};
