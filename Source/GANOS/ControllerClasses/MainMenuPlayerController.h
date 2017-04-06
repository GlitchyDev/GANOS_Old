// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GANOS_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMainMenuPlayerController();
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable, Category="C++")
    void ConnectMultiplayer(FString Username, FString Password);
    
    virtual void SetupInputComponent() override;
    
	
};
