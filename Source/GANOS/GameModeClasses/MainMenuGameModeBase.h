// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ServerMainMenuLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ClientMainMenuLog, Log, All);

USTRUCT()
struct FAuthentication
{
    GENERATED_USTRUCT_BODY()
    FString Username;
    FString Password;
    FAuthentication()
    {this->Username = FString("");this->Password = FString("");}
    FAuthentication(FString Username, FString Password)
    {this->Username = Username;this->Password = Password;}
    bool CheckAuthentication(FString PosUsername,FString PosPassword)
    {return (Username.Equals(PosUsername) && Password.Equals(PosPassword));}
    bool CheckAuthentication(FAuthentication Authentication)
    {return (Username.Equals(Authentication.Username) && Password.Equals(Authentication.Password));}
    FString ToString(){FString S = FString();S.Append("{");S.Append(Username);S.Append("|");S.Append(Password);S.Append("}");return S;}
};

UCLASS()
class GANOS_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    AMainMenuGameModeBase();
    
    virtual void BeginPlay() override;
    virtual void PreLogin(const FString & Options,const FString & Address,const TSharedPtr < const FUniqueNetId > & UniqueId,FString & ErrorMessage) override;
    virtual APlayerController* Login(class UPlayer * NewPlayer,ENetRole InRemoteRole,const FString & Portal,const FString & Options,const TSharedPtr < const FUniqueNetId > & UniqueId,FString & ErrorMessage) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController * Exiting) override;
	
    void GoToBattleMap();

    
    TArray<FAuthentication> AuthenticationList;
	
	
	
};
