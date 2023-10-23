// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/CTutoEnemy.h"

// Sets default values
ACTutoEnemy::ACTutoEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACTutoEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACTutoEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACTutoEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

