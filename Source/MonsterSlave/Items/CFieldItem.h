#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/ItemStruct.h"
#include "CFieldItem.generated.h"

UCLASS()
class MONSTERSLAVE_API ACFieldItem : public AActor
{
	GENERATED_BODY()
public:	
	ACFieldItem();
protected:
	virtual void BeginPlay() override;
// ==================================================================
private:

// ==================================================================
private:
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnInteract();
// ==================================================================
public:
	UPROPERTY(EditDefaultsOnly, Category = "Description")
		class UCItemData* ItemDescription;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UPaperSpriteComponent* MinimapSprite;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

private:
	class TSubclassOf<UUserWidget> InteractWidgetClass;
	class UCInteract* InteractWidget;
};
