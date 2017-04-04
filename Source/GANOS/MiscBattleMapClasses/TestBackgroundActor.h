// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TestBackgroundActor.generated.h"

UCLASS()
class GANOS_API ATestBackgroundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestBackgroundActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    UStaticMeshComponent* MeshComp;
    

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    float PitchAnglePerSecond;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    float RollAnglePerSecond;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    float YawAnglePerSecond;
    
	
};
