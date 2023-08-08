// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlayerHair.generated.h"

UCLASS()
class MONSTERSLAVE_API ACPlayerHair : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPlayerHair();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	static ACPlayerHair* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

// ======================================================
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	class USkeletalMesh* PlayerHair;
	class ACharacter* Owner;
	FName HairSocket = "hair_socket";
};
