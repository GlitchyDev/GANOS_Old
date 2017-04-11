// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SchemaClasses/BaseSchemaPawn.h"
#include "WapnSchemaPawn.generated.h"

/**
 * This Schema is based on the Chesspiece "Pawn"
 As per other members of the Chess Schema, it gains an additional ability if a King Schema is in play ( The ability to Promote into another Schema )
 This was also probably the first Schema properly implemented :D
 
 
 AttackConfiguration:
 It will advance to the opponents side of the board, and on reaching the end will either reset or promote (If a King is present)
 If a opponent is in the diagnal panel, it will attack the opponent and reset to the back of its side of the board
 
 Defend Configuration:
 It will not attack unless a valid enemy moves into a diagnal panel, otherwise it will idle
 When it does attack it will always teleport back to the original panel
 
 Support Configuration
 It is placed on the opponents side of the battle field, and when an opponent moves to the side of it, it will EnPassent it and then reset to the original panel. This is an alternative form of defend.

 
 Attack:
 - If it passes the half way point and has a valid target it'll do the deal damage and teleport back
 
 
 
 
 On the Todo list for this class we need to
 - Implement the other Configurations
 - Clean up the code base, its too cluttered for my taste
 - Re-do the Sprite and add some more impresive animations
 */
UCLASS()
class GANOS_API AWapnSchemaPawn : public ABaseSchemaPawn
{
    GENERATED_BODY()
public:
    AWapnSchemaPawn();
    
    virtual void BeginPlay() override;
    virtual void SchemaTick(float DeltaSeconds) override;
    virtual void RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount) override;
    virtual void DealDamage(ABaseSchemaPawn* Schema) override;
    virtual void OnConstruction(const FTransform & Transform) override;
    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
    virtual void UpdateHealthBar() override;
    virtual void UpdateNameTag() override;

    // GENERAL METHODS
    
    /**
     Triggers any Wapn logic that is needed
     */
    void WapnLogic();
    /**
     Triggers any Wapn animations that is needed
     */
    void WapnAnimate();

    
    // SERVER LOGIC FUNCTIONS
    /**
     A Method that figures out which side is the Wapns side, and picks a random tile from the farthest out point, if it fails the Wapn will be set back into idle mode
     */
    void Relocate();
    // Promote into a different Chess Schema*
    //void Promote();
    
    /**
     Removes any Logic markers added during Attacks, Moves, Death, ect so it can switch to another state
     */
    void ClearMarkingStatuses();
    
    /**
     Attempts to generate an Attack path
     Prioritizes
     - Attacks
     - Moves
     - If none, relocate
     Plan: Add in El-Passant detection
     */
    bool GenerateAttackPath();
    /**
     UNDEVELOPED
     This one would stay in one place until an attack comes along
     */
    bool GenerateDefendPath();
    /**
     UNDEVELOPED
     This one would try to race across to the other side of the board to promote itself
     */
    bool GenerateSupportPath();
    

    
    
    // CLIENT ANIMATION METHODS
    /*
     Used to add the Sprite component visuals
     Plan: Only add the Components on Clients that NEED it ( No Dedicated Server )
     */
    void CreateWapnVisual();
    /**
     Animates Wapn to do the standard idle animation
     Plan: Make the time between blinks randomish, and add some more facial expresions
     */
    void AnimateWapnIdle();
    /**
     Slides Wapn across the screen with a Serious expression on its face
     Plan: Make the serious expression pop up before it moves, and add a ending animation
     */
    void AnimateWapnMove();
    /**
     A Animated Wapn attack where it jumps and aims for the tile its attacking
     Plan: Add some particle effects for the attack and the relocation, and an animation when it fails
     */
    void AnimateWapnAttack();
    /**
     A animated Wapn hurt expresion
     Plan: Add some color changes
     */
    void AnimateWapnHurt();
    /**
     A animated slide down through the panel
     Plan: Add an animated disolve sequence
     */
    void AnimateWapnDying();
    
    
    

    
    

    // SPRITE COMPONENTS and SPRITES
    UPaperSpriteComponent* Wapn_Body_Sprite_Comp;
    UPaperSpriteComponent* Wapn_Eye_Sprite_Comp;
    UPaperSprite* Wapn_Body_Sprite;
    UPaperSprite* Wapn_Idle_Eye_1_Sprite;
    UPaperSprite* Wapn_Idle_Eye_2_Sprite;
    UPaperSprite* Wapn_Idle_Eye_3_Sprite;
    UPaperSprite* Wapn_Hurt_Eye_1_Sprite;
    UPaperSprite* Wapn_Hurt_Eye_2_Sprite;
    
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
    
    
    // WAPN needed Instance Variables
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
    
    /*
     This will determine how many bars the Healthbar is
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 SizeOfHealthBar;
    

    
    
    
};
