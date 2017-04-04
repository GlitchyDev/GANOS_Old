// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "EnumHeaders/SchemaEnums.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "StateClasses/BattleMapGameStateBase.h"
#include "MiscBattleMapClasses/BattleTileActor.h"
#include "BaseSchemaPawn.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BaseSchemaLog, Log, All);

UCLASS()
class GANOS_API ABaseSchemaPawn : public APawn
{
	GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABaseSchemaPawn();
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    // These methods are INTENDED to be overriden in order to provide individuality to inherited classes
    
    // The Schemas Version of the Tick, used to run Schema Methods
    virtual void SchemaTick(float DeltaSeconds);
    //Take damage and do appropriate animations and State changes
    virtual void RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount);
    // Specifies that the Schema will attack another, allowing the Child Class to specify any details
    virtual void DealDamage(ABaseSchemaPawn* Schema);
    
    EGANOSNetworkRoleEnum DetermineNetworkRole();
    
    
    
    // Use to posses a tile, used when a Schema is larger than one tile
    void PossesTile(uint8 X, uint8 Y);
    // Used to unposses a tile
    void UnpossesTile(uint8 X, uint8 Y);
    // Figures out where the Schema's base needs to be
    FVector GenerateDefaultPosition();
    FVector GenerateDefaultPosition(uint8 X, uint8 Y);
    
    
    
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    FString DisplayName;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 MaxHealth;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 CurrentHealth;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 X;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 Y;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    ESchemaTypeEnum SchemaType;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    ETeamEnum SchemaTeam;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    ESchemaBattleConfigurationEnum SchemaConfigurationType;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    ESchemaStateEnum SchemaState;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    float SchemaStateStartTime;
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    TArray<ESchemaStatusEnum> SchemaStatuses;
    
    class ABattleMapGameStateBase* GameState;
    
};
