// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "BaseSchemaPawn.h"


// Sets default values
ABaseSchemaPawn::ABaseSchemaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSchemaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSchemaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseSchemaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

