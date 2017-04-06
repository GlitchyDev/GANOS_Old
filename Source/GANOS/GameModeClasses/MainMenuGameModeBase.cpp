// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "MainMenuGameModeBase.h"
#include "ControllerClasses/MainMenuPlayerController.h"
#include "StateClasses/MainMenuGameStateBase.h"
#include "StateClasses/MainMenuPlayerState.h"

DEFINE_LOG_CATEGORY(ServerMainMenuLog);
DEFINE_LOG_CATEGORY(ClientMainMenuLog);


AMainMenuGameModeBase::AMainMenuGameModeBase()
{
    PlayerStateClass = AMainMenuPlayerState::StaticClass();
    GameStateClass = AMainMenuGameStateBase::StaticClass();
    HUDClass = AHUD::StaticClass();
    PlayerControllerClass = AMainMenuPlayerController::StaticClass();
    DefaultPawnClass = NULL;
    
    bUseSeamlessTravel = true;
    
    AuthenticationList.Add(FAuthentication(FString("Defoko"),FString("UTAU")));
    AuthenticationList.Add(FAuthentication(FString("Devotedworker"),FString("MurderFace")));
}

void AMainMenuGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}


void AMainMenuGameModeBase::PreLogin (const FString & Options,const FString & Address,const TSharedPtr < const FUniqueNetId > & UniqueId, FString & ErrorMessage)
{
    if (GetNetMode() == ENetMode::NM_DedicatedServer)
    {
        FString Username = UGameplayStatics::ParseOption(Options,TEXT("Username"));
        FString Password = UGameplayStatics::ParseOption(Options,TEXT("Password"));
        bool Approved = false;
        UE_LOG(ServerMainMenuLog, Warning,TEXT("Recieved Authentication {%s|%s}"), *Username, *Password);
        FAuthentication ClientAuthentication = FAuthentication(Username,Password);
        UE_LOG(ServerMainMenuLog, Warning,TEXT("Created Authentication Structure %s"), *ClientAuthentication.ToString());
        
        for (auto& ApprovedAuthentication : AuthenticationList)
        {
            UE_LOG(ServerMainMenuLog, Warning,TEXT("Comparing Structures %s to %s"), *ClientAuthentication.ToString(), *ApprovedAuthentication.ToString());
            
            if (ClientAuthentication.CheckAuthentication(ApprovedAuthentication))
            {
                UE_LOG(ServerMainMenuLog, Warning,TEXT("Login Approved!"));
                
                Approved = true;
            }
        }
        if (Approved)
        {
            UE_LOG(ServerMainMenuLog, Warning,TEXT("Login Absolutely Approved"));
            
        }
        else
        {
            UE_LOG(ServerMainMenuLog, Warning,TEXT("Login Failed!"));
            ErrorMessage = FString("Invalid Login");
            
        }
    }
}

APlayerController* AMainMenuGameModeBase::Login(class UPlayer * NewPlayer,ENetRole InRemoteRole,const FString & Portal,const FString & Options,const TSharedPtr < const FUniqueNetId > & UniqueId,FString & ErrorMessage)
{
    AMainMenuPlayerController* PlayerController = Cast<AMainMenuPlayerController>(SpawnPlayerController(ENetRole::ROLE_None, FVector(0,0,0), FRotator(0,0,0)));
    if(GetNetMode() == ENetMode::NM_DedicatedServer)
    {
        FString Username= UGameplayStatics::ParseOption(Options, TEXT("Username"));
        UE_LOG(ServerMainMenuLog, Warning,TEXT("Creating PlayerController for %s"), *Username);
        PlayerController->SetName(*Username);
    }
    return PlayerController;
}

void AMainMenuGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    /*
     APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(),0);
     pc->ClientTravel(FString(TEXT("216.130.133.37")),TRAVEL_Absolute);
     GetWorld()->Exec(GetWorld(), TEXT("open 127.0.0.1:7777?password=userPsw?login=userLogin"));
     */
    if (GetNetMode() == ENetMode::NM_DedicatedServer)
    {
        FTimerHandle UnusedHandle;
        UE_LOG(ServerMainMenuLog, Warning,TEXT("Creating Delayed Action!"));
        
        GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMainMenuGameModeBase::GoToBattleMap, 1, false);
    }
}


void AMainMenuGameModeBase::Logout(AController* Exiting)
{
    
}


void AMainMenuGameModeBase::GoToBattleMap()
{
    UE_LOG(ServerMainMenuLog, Warning,TEXT("Executing Delayed Action!"));

    GetWorld()->ServerTravel("/Game/TestingBattleWorld");
}
