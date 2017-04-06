// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "MainMenuPlayerController.h"





AMainMenuPlayerController::AMainMenuPlayerController()
{
    /*
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++")
     TSubclassOf<class UUserWidget> wMainMenu;
     
     
     UUserWidget* MyMainMenu;
     */
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    DefaultMouseCursor = EMouseCursor::EyeDropper;
    bAutoManageActiveCameraTarget = false;
}

void AMainMenuPlayerController::BeginPlay()
{
    
}


void AMainMenuPlayerController::ConnectMultiplayer(FString Username, FString Password)
{
    UGameplayStatics::GetPlayerController(GetWorld(),0)->ClientTravel(FString("127.0.0.1?Username=" + Username + "?Password=" + Password),ETravelType::TRAVEL_Absolute);
}

void AMainMenuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    //InputComponent->BindAction("UP", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::LoginTest);
    //InputComponent->BindAction("DOWN", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::ModifyLogin);
    //InputComponent->BindAction("LEFT", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::TT);
    //InputComponent->BindAction("RIGHT", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::MapName);
    //InputComponent->BindAction("A", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::DetectConnection);
    //InputComponent->BindAction("Q", EInputEvent::IE_Pressed, this, &AMainMenuPlayerController::EQuit);
    //     pc->ClientTravel(FString("127.0.0.1?Username=Devotedworker?Password=MurderFace"),ETravelType::TRAVEL_Absolute);
    
    
    
    
    
    //InputComponent->BindAction("UP", IE_Pressed, this, &AMainMenuPlayerController::b);
}

