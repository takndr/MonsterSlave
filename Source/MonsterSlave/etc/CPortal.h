#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPortal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPortalSaveSignature);

UCLASS()
class MONSTERSLAVE_API ACPortal : public AActor
{
	GENERATED_BODY()
public:	
	ACPortal();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
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
public:
	FPortalSaveSignature OnPortalSave;

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
		FString NextMap;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* PortalParticle;
};
