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

    ABaseSchemaPawn();
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    // These methods are INTENDED to be overriden in order to provide individuality to inherited classes
    
    /**
     Schemas version of the Tick function
     - Overriden in the Subclasses to add AI Functionality
     - Overriden in the Subclass to add Animation Functionality
     */
    virtual void SchemaTick(float DeltaSeconds);
    /**
     Schemas way of recieving damage, inflicted to their current Health
     If the Schema would die from recieving damage, this function will trigger it
     @param Attacker - The Schema iniciating the attack ( Tile damage is addressed as whoever placed the effect )
     @param Type - The "Type" of damage being inflicted, some damage such as Logical may deal more damage to Schemas with the Empethetical typing
     @param DamageAmount - How much damage is being inflicted
    */
    virtual void RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount);
    /**
     Schemas way of dealing damage
     All things required on dealing damage such as state changes will be added here
     @param Schema - The Schema recieving the damage
     */
    virtual void DealDamage(ABaseSchemaPawn* Schema);
    
    
    /**
     A Notification to update the Health Bar
     Triggered when the MaxHealth or Current Health Changes
     Implemented by Subclass
     */
    virtual void UpdateHealthBar();
    /**
     A Notification to update the NameTag
     Triggered when the Name changes
     Implemented by SubClass
     */
    virtual void UpdateNameTag();
    
    UFUNCTION()
    void OnRep_MaxHealth();
    UFUNCTION()
    void OnRep_CurrentHealth();
    UFUNCTION()
    void OnRep_DisplayName();
    
    /**
     Used for easy determination of the Client State of the current Game Instance, will likely be moved to an automatically implemented header later
     */
    EGANOSNetworkRoleEnum DetermineNetworkRole();
    
    
    
    /**
     Allows the Schema to "Posses" the tile, dealing damage on that tile will in turn deal damage to the Schema 
     - Used when Visually the Schema is ON that tile, other methods should be used if its just rendering the tile removed
     */
    void PossesTile(uint8 X, uint8 Y);
    /**
     Allows the Schema to "UnPosses" the tile, removing itself from that tile
     - Used when the Schema is no longer visible on that tile and shouldn't recieve damage there
     */
    void UnpossesTile(uint8 X, uint8 Y);
    /**
     Gets FVector of the Current Location of the Tile who fits the Schemas X and Y
     */
    FVector GenerateDefaultPosition();
    /**
     Gets FVector of the Tile specified
     @param X - The Tile X
     @param Y - The Tile Y
     */
    FVector GenerateDefaultPosition(uint8 X, uint8 Y);
    
    
    // Base Variables added and in need of onRep Functions
    UPROPERTY(ReplicatedUsing=OnRep_DisplayName, EditAnywhere, BlueprintReadWrite, Category="C++")
    FString DisplayName;
    UPROPERTY(ReplicatedUsing=OnRep_MaxHealth, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 MaxHealth;
    UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 CurrentHealth;
    // ALL OF THESE NEED TO BE REPLICATED FOR CLIENT VISUAL USE!
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
    // The Gamestate, for convinience of not using the stupid UGameplayStatic thing every single time                                                                                                                                   
    class ABattleMapGameStateBase* GameState;
    
};
