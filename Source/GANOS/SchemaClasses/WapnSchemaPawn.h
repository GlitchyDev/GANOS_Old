// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SchemaClasses/BaseSchemaPawn.h"
#include "WapnSchemaPawn.generated.h"

/**
 * This Schema is based on the Chesspiece "Pawn"
 As per other members of the Chess Schema, it gains an additional ability if a King Schema is in play
 This was also the first Schema properly implemented :D
 
 
 AttackConfiguration:
 It will advance to the opponents side of the board, and on reaching the end will either reset or promote (If a King is present)
 If a opponent is in the diagnal panel, it will attack the opponent and reset to the back of its side of the board
 
 Defend Configuration:
 It will not attack unless a valid enemy moves into a diagnal panel, otherwise it will idle
 When it does attack it will always teleport back to the original panel
 
 Support Configuration
 It is placed on the opponents side of the battle field, and when an opponent moves to the side of it, it will EnPassent it and then reset to the original panel. This is an alternative form of defend.
 
 Idle Needs to
 - Animate ( Preferably with realistic emotions )
 - When Idle times out, generate path and switch to the appropriate mode
 
 Attack:
 - If it passes the half way point and a valid target it'll do the deal damage and teleport back
 
 
 
 
 // Ok so we need to
 // Restructure the game allow the use of a dedicated server ( Not much, as the Gamemode isn't replicated ( not that we need it )
 // Thankfully the Gamestate carries over so we know that we at least have our Tile and Actor List
 
 // Animations can be done on the Server and Replicated to the Client
 // AI needs to be done on the Authority, ( Singleplayer or DedicatedServer/Host )
 // The AI changes need to reflect on the Client ( If its Singleplayer, just have an avaliable else in SchemaTick
 // Variables need to replicate
 // Anything that would affect a Clients output that would eliminate unintentional input
 // Anything the Client needs for Player Visuals ( Name, Chips, HP, Ect )
 // If the Replicated Movement is a pain we will use anything needed for animations
 */
UCLASS()
class GANOS_API AWapnSchemaPawn : public ABaseSchemaPawn
{
    GENERATED_BODY()
public:
    AWapnSchemaPawn();
    
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform & Transform) override;
    virtual void SchemaTick(float DeltaSeconds) override;
    virtual void RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount) override;
    virtual void DealDamage(ABaseSchemaPawn* Schema) override;
    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
    
    virtual void UpdateHealthBar() override;
    virtual void UpdateNameTag() override;
    
    // Creates and Loads the Default Sprites
    void CreateWapnVisual();
    
    // Called when a Change to the Schemas name happens
    //void UpdateNameTag();
    // Called when Health Changes
    //void UpdateHealthTag();
    
    // The Default Schema Idle Animation... Blinking, doing facial expresions ect.
    void AnimateWapnIdle();
    // A Simple Slide from the Current X/Y to the TargetTileX/Y, add some sort of eye expression
    void AnimateWapnMove();
    // A Simple Animated jump from the Current X/Y to the TargetTileXY
    // Preferably the eye of the Wapn would have a "prepaired" face and then a "SHIT WTF AHHHH" Face until it lands
    void AnimateWapnAttack();
    // A Red Flash and the Hurt Eyes
    void AnimateWapnHurt();
    // A Closing of Eyes and Sink
    void AnimateWapnDying();
    
    // Figures out where it needs to go after Reaching the Opponents Side*
    void Relocate();
    // Promote into a different Chess Schema*
    //void Promote();
    
    // Does the Logic needed for the Authority
    void WapnLogic();
    // Does the Visuals needed for the Client
    void WapnAnimate();
    
    // Clears any AI markers that are not required for normal function
    void ClearMarkingStatuses();
    
    bool GenerateAttackPath();
    bool GenerateDefendPath();
    bool GenerateSupportPath();
    // Generate Attack Path ( Generates path then decides if to advance or attack)
    // Generate Defence Path ( Check for Diagnal, false if nobody is there )
    // Generate Support Path ( Check for sides )
    
    UPaperSpriteComponent* Wapn_Body_Sprite_Comp;
    UPaperSpriteComponent* Wapn_Eye_Sprite_Comp;
    UPaperSprite* Wapn_Body_Sprite;
    UPaperSprite* Wapn_Idle_Eye_1_Sprite;
    UPaperSprite* Wapn_Idle_Eye_2_Sprite;
    UPaperSprite* Wapn_Idle_Eye_3_Sprite;
    UPaperSprite* Wapn_Hurt_Eye_1_Sprite;
    UPaperSprite* Wapn_Hurt_Eye_2_Sprite;
    
    /*
     This is the X of the Current Target Panel
     If No Panel is being Seeked 0 will be used
     */
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 TargetTileX;
    /*
     This is the Y of the Current Target Panel that is being moved to
     If No Panel is being Seeked 0 will be used
     */
    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 TargetTileY;
    /*
     This is the X of the Panel Wapn Started on
     Attack Mode: This panel will be excluded when the Schema Teleports back (Assuming it doesn't Promote) if able
     Defence Mode: This panel will be where the Schema Teleports back to after completing its attack
     Support Mode:: This panel will be where the Schema Teleports back to after completing its attack
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 StartingTileX;
    /*
     This is the Y of the Panel Wapn Started on
     Attack Mode: The X the Wapn Started on, used for animations
     Defence Mode: This panel will be where the Schema Teleports back to after completing its attack
     Support Mode:: This panel will be where the Schema Teleports back to after completing its attack
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 StartingTileY;
    /*
     Determine if Wapn is Attacking
     Attack Mode: The Y  the Wapn Started on, used for animations
     Defence Mode: Always used
     Support Mode: Always used
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    bool Attacking;
    /*
     This will determine if the Wapn can make a Double Step movement
     Attack Mode: Assuming its the Schemas first move, this will allow it to use a double step move
     Defence Mode: No Use
     Support Mode: No Use
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    bool DoubleStep;
    /*
     If the Schema makes to the far side of the board, if there is a King on the Board, it will promote
     Attack Mode: The only mode this is avalible on
     Defence Mode: No Use
     Support Mode: No Use
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    bool Promotable;
    
    // This is all the Same Regardless of Schema
    // ***************************
    
    /*
     This will determine how many bars the Healthbar is
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 SizeOfHealthBar;
    
    // This is the base of the ENTIRE Actor It keeps the Nametag and SpriteBase relative
    class UArrowComponent* Base;
    // This is the Base of the Sprites, use this to trascribe and rotate the entire sprite model but not the name
    class UArrowComponent* SpriteBase;
    // This is the Base of the Nametag System, don't mess with this too much
    class UArrowComponent* NameBase;
    
    // This is where the "Name" of the Schema ( Monster ) is put, have it take it from SchemaName and add stuff if needed
    class UTextRenderComponent* NameTag;
    // This is where the "Health" of the Schema ( Monster ) is put, using a varied amount of Bars turning into spaces for Percentage
    class UTextRenderComponent* HealthBar;
    
    
    
};
