// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "WapnSchemaPawn.h"
#include "EnumHeaders/SchemaEnums.h"
#include "UnrealNetwork.h"
#include "MiscBattleMapClasses/BattleTileActor.h"


AWapnSchemaPawn::AWapnSchemaPawn()
{
    CreateWapnVisual();
    
    
    DisplayName = "Wapn";
    MaxHealth = 5;
    CurrentHealth = 5;
    SizeOfHealthBar = 5;
    SchemaType = ESchemaTypeEnum::STE_WAPN;
    DoubleStep = true;
    TargetTileX = 0;
    TargetTileY = 0;
    
    UpdateNameTag();
    UpdateHealthTag();
    switch((uint8)SchemaConfigurationType)
    {
        case ((uint8)ESchemaBattleConfigurationEnum::BTE_ATTACK):
            SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_IDLE;
            break;
        case ((uint8)ESchemaBattleConfigurationEnum::BTE_DEFEND):
            SchemaState = ESchemaStateEnum::SSE_WAPN_DEF_IDLE;
            break;
        case ((uint8)ESchemaBattleConfigurationEnum::BTE_SUPPORT):
            SchemaState = ESchemaStateEnum::SSE_WAPN_SUP_IDLE;
            break;
    }
    
}


void AWapnSchemaPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AWapnSchemaPawn, TargetTileX);
    DOREPLIFETIME(AWapnSchemaPawn, TargetTileY);
}


void AWapnSchemaPawn::OnConstruction(const FTransform & Transform)
{
    switch((uint8)SchemaTeam)
    {
        case ((uint8)ETeamEnum::TTE_WHITE):
            Wapn_Body_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Wapn_Eye_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            NameTag->SetTextRenderColor(FColor(0,0,0));
            HealthBar->SetTextRenderColor(FColor(0,0,0));
            SpriteBase->SetWorldScale3D(FVector(1,1,1));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Wapn Color White"));
            break;
        case ((uint8)ETeamEnum::TTE_BLACK):
            Wapn_Body_Sprite_Comp->SetSpriteColor(FColor(150,150,150));
            Wapn_Eye_Sprite_Comp->SetSpriteColor(FColor(150,150,150));
            NameTag->SetTextRenderColor(FColor(0,0,0));
            HealthBar->SetTextRenderColor(FColor(0,0,0));
            SpriteBase->SetWorldScale3D(FVector(-1,1,1));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Wapn Color Black"));
            break;
        default:
            Wapn_Body_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Wapn_Eye_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            NameTag->SetTextRenderColor(FColor(0,0,0));
            HealthBar->SetTextRenderColor(FColor(0,0,0));
            SpriteBase->SetWorldScale3D(FVector(1,1,1));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Wapn Color Default"));
            break;
    }
    UpdateNameTag();
    UpdateHealthTag();
}
void AWapnSchemaPawn::CreateWapnVisual()
{
    Base = CreateDefaultSubobject<UArrowComponent>(TEXT("ActorBase"));
    Base->SetVisibility(false);
    Base->SetRelativeRotation(FRotator(0,0,0));
    Base->AttachTo(RootComponent);
    
    SpriteBase = CreateDefaultSubobject<UArrowComponent>(TEXT("SpriteBase"));
    SpriteBase->SetVisibility(false);
    SpriteBase->SetRelativeRotation(FRotator(0,270,0));
    SpriteBase->AttachTo(Base);
    
    NameBase = CreateDefaultSubobject<UArrowComponent>(TEXT("NameBase"));
    NameBase->SetVisibility(false);
    NameBase->SetRelativeRotation(FRotator(0,180,0));
    NameBase->AttachTo(Base);
    
    NameTag = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameTag"));
    NameTag->SetRelativeLocationAndRotation(FVector(0,0,350), FRotator(0,0,0));
    NameTag->SetWorldSize(50.0);
    NameTag->SetText("BROKEN NAMETAG UPDATE");
    NameTag->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    NameTag->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    NameTag->AttachTo(NameBase);
    
    
    HealthBar = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthBar"));
    HealthBar->SetRelativeLocationAndRotation(FVector(0,0,310), FRotator(0,0,0));
    HealthBar->SetWorldSize(50.0);
    HealthBar->SetText("BROKEN HEALTHBAR UPDATE");
    HealthBar->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    HealthBar->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    HealthBar->AttachTo(NameBase);
    
    Wapn_Body_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Wapn_Body_Sprite_Comp"));
    Wapn_Eye_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Wapn_Eye_Sprite_Comp"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Body_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Body_Sprite.Wapn_Body_Sprite'"));
    
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Idle_Eye_1_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Eye_Idle_1_Sprite.Wapn_Eye_Idle_1_Sprite'"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Idle_Eye_2_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Eye_Idle_2_Sprite.Wapn_Eye_Idle_2_Sprite'"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Idle_Eye_3_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Eye_Idle_3_Sprite.Wapn_Eye_Idle_3_Sprite'"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Hurt_Eye_1_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Eye_Hurt_1_Sprite.Wapn_Eye_Hurt_1_Sprite'"));
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Wapn_Hurt_Eye_2_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Wapn/Wapn_Eye_Hurt_2_Sprite.Wapn_Eye_Hurt_2_Sprite'"));
    
    
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Paper2D/DefaultLitSpriteMaterial.DefaultLitSpriteMaterial'"));
    UMaterial* SpriteMaterial = (UMaterial*)Material.Object;
    
    
    Wapn_Body_Sprite = Wapn_Body_SpriteObj.Object;
    Wapn_Idle_Eye_1_Sprite = Wapn_Idle_Eye_1_SpriteObj.Object;
    Wapn_Idle_Eye_2_Sprite = Wapn_Idle_Eye_2_SpriteObj.Object;
    Wapn_Idle_Eye_3_Sprite = Wapn_Idle_Eye_3_SpriteObj.Object;
    Wapn_Hurt_Eye_1_Sprite = Wapn_Hurt_Eye_1_SpriteObj.Object;
    Wapn_Hurt_Eye_2_Sprite = Wapn_Hurt_Eye_2_SpriteObj.Object;
    
    Wapn_Body_Sprite_Comp->SetSprite(Wapn_Body_Sprite);
    Wapn_Body_Sprite_Comp->SetRelativeLocation(FVector(0,0,135));
    Wapn_Body_Sprite_Comp->SetRelativeScale3D(FVector(1,1,1));
    Wapn_Body_Sprite_Comp->SetRelativeRotation(FRotator(0,0,0));
    Wapn_Body_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_1_Sprite);
    Wapn_Eye_Sprite_Comp->SetRelativeLocation(FVector(-29,-0.2,226));
    Wapn_Eye_Sprite_Comp->SetRelativeScale3D(FVector(1,1,1));
    Wapn_Eye_Sprite_Comp->SetRelativeRotation(FRotator(0,0,0));
    Wapn_Eye_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    
    Wapn_Body_Sprite_Comp->AttachTo(SpriteBase);
    Wapn_Eye_Sprite_Comp->AttachTo(SpriteBase);
}
void AWapnSchemaPawn::UpdateHealthTag()
{
    double healthPercentage = (1.0 / MaxHealth) * CurrentHealth;
    int FullHealthBars = SizeOfHealthBar * healthPercentage;
    int EmptyHealthBars = SizeOfHealthBar - FullHealthBars;
    FString FullBar = "|";
    FString EmptyBar = " ";
    FString Name = "[";
    for(int i = 0; i < FullHealthBars; i++){Name = Name + FullBar;}
    for(int i = 0; i < EmptyHealthBars; i++){Name = Name + EmptyBar;}
    Name = Name + "]";
    HealthBar->SetText(Name);
    
}
void AWapnSchemaPawn::UpdateNameTag()
{
    FString Name = DisplayName;
    NameTag->SetText(Name);
    
}

void AWapnSchemaPawn::BeginPlay()
{
    Super::BeginPlay();
    SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
    
}

void AWapnSchemaPawn::SchemaTick(float DeltaSeconds)
{
    Super::SchemaTick(DeltaSeconds);
    switch((uint8)DetermineNetworkRole())
    {
        case (uint8)EGANOSNetworkRoleEnum::GNRE_ANIMATE_AND_LOGIC:
            WapnLogic();
            WapnAnimate();
            break;
        case (uint8)EGANOSNetworkRoleEnum::GNRE_LOGIC_ONLY:
            WapnLogic();
            break;
        case (uint8)EGANOSNetworkRoleEnum::GNRE_ANIMATE_ONLY:
            WapnAnimate();
            break;
    }
}

/*
 virtual void RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount) override;
 virtual void DealDamage(ABaseSchemaPawn* Schema) override;
 */

void AWapnSchemaPawn::RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount)
{
    CurrentHealth -= DamageAmount;
    if(CurrentHealth <= 0)
    {
        SchemaState = ESchemaStateEnum::SSE_WAPN_DYING;
        SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
        // Make it "dead" imediately
        GameState->ClearOwnerShip(this);
    }
    else
    {
        SchemaState = ESchemaStateEnum::SSE_WAPN_DAMAGED;
        SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
    }
    UpdateHealthTag();
}

void AWapnSchemaPawn::DealDamage(ABaseSchemaPawn* Schema)
{
    Schema->RecieveDamage(this,EDamageTypeEnum::DTE_DEBUG,1);
    Relocate();
}

void AWapnSchemaPawn::WapnLogic()
{
    // Measured from 0.0 - 1.0
    float MovementAnimationProgress = (1.0/5.0) * (GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime);
    
    
    switch((uint8)SchemaState)
    {
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_IDLE:
            if ((GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime) >= 5)
            {
                if(GenerateAttackPath())
                {
                    if(Attacking)
                    {
                        SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_ATTACK;
                    }
                    else
                    {
                        
                        SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_MOVE;
                    }
                }
                SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
            }
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_ATTACK:
            if(GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime > 0.25)
            {
                for (ABaseSchemaPawn* Schema : GameState->GetTile(TargetTileX,TargetTileY)->CurrentSchemas)
                {
                    DealDamage(Schema);
                }
                
               // if(GameState->GetTile(TargetX,TargetY);
            }
// ********************
            break;
            
        
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_MOVE:
            if(SchemaStatuses.Contains(ESchemaStatusEnum::SEE2_WAPN_DOUBLESTEP))
            {
                int8 Direction;
                switch((uint8)SchemaTeam)
                {
                    case ((uint8)ETeamEnum::TTE_WHITE):
                        Direction = 1;
                        break;
                    case ((uint8)ETeamEnum::TTE_BLACK):
                        Direction = -1;
                        break;
                        
                }
                if(!SchemaStatuses.Contains(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_1) && (MovementAnimationProgress >= 0.25))
                {
                    if(GameState->GetTile(X + Direction, Y)->IsHabitable())
                    {
                        GameState->ClearOwnerShip(this);
                        SchemaStatuses.Add(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_1);
                        PossesTile(X + Direction, Y);
                    }
                    else
                    {
                        Relocate();
                    }
                }
                else {
                    if(GameState->GetTile(TargetTileX, TargetTileY)->IsHabitable() || SchemaStatuses.Contains(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_2))
                    {
                        if(!SchemaStatuses.Contains(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_2) && (MovementAnimationProgress >= 0.75))
                        {
                            GameState->ClearOwnerShip(this);
                            SchemaStatuses.Add(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_2);
                            PossesTile(TargetTileX, TargetTileY);
                        }
                    }
                    else
                    {
                        Relocate();
                    }
                }
            }
            else
            {
                if(!SchemaStatuses.Contains(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK) && (MovementAnimationProgress >= 0.5))
                {
                    
                    if(GameState->GetTile(TargetTileX, TargetTileY)->IsHabitable())
                    {
                        SchemaStatuses.Add(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK);
                        GameState->ClearOwnerShip(this);
                        PossesTile(TargetTileX, TargetTileY);
                    }
                    else
                    {
                        Relocate();
                    }
                }
            }
            
            
            if ((GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime) >= 5)
            {
                UE_LOG(LogTemp, Warning, TEXT("Complete!"));
                
                SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_IDLE;
                X = TargetTileX;
                Y = TargetTileY;
                SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
                SchemaStatuses.Remove(ESchemaStatusEnum::SEE2_WAPN_DOUBLESTEP);
                SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK);
                SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_1);
                SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_2);
                
            }
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DEF_IDLE:
            //WapnDefIdle();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DEF_ATTACK:
            //WapnDefAttack();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_SUP_ATTACK:
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DAMAGED:
            if((GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime) > 2)
            {
                switch((uint8)SchemaConfigurationType)
                {
                    case ((uint8)ESchemaBattleConfigurationEnum::BTE_ATTACK):
                        SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_IDLE;
                        break;
                    case ((uint8)ESchemaBattleConfigurationEnum::BTE_DEFEND):
                        SchemaState = ESchemaStateEnum::SSE_WAPN_DEF_IDLE;
                        break;
                    case ((uint8)ESchemaBattleConfigurationEnum::BTE_SUPPORT):
                        SchemaState = ESchemaStateEnum::SSE_WAPN_SUP_IDLE;
                        break;
                    case ((uint8)ESchemaBattleConfigurationEnum::BTE_GLITCH):
                        SchemaState = ESchemaStateEnum::SSE_DUMMY;
                        break;
                        
                }
                SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
            }
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DYING:
            if((GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime) > 5)
            {
                Destroy();
            }
            
            break;
    }
}
void AWapnSchemaPawn::WapnAnimate()
{
    
    switch((uint8)SchemaState)
    {
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_IDLE:
            AnimateWapnIdle();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_ATTACK:
            AnimateWapnAttack();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_ATK_MOVE:
            AnimateWapnMove();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DEF_IDLE:
            //WapnDefIdle();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DEF_ATTACK:
            //WapnDefAttack();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_SUP_ATTACK:
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DAMAGED:
            AnimateWapnHurt();
            break;
        case (uint8)ESchemaStateEnum::SSE_WAPN_DYING:
            AnimateWapnDying();
            break;
        case (uint8)ESchemaStateEnum::SSE_DUMMY:
            AnimateWapnIdle();
            break;
    }
}



void AWapnSchemaPawn::AnimateWapnIdle()
{
    float AnimationProgress3s = fmod((UGameplayStatics::GetTimeSeconds(GetWorld()) - SchemaStateStartTime), 3.0);
    if(AnimationProgress3s < 2.6)
    {
        Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_1_Sprite);
    }
    else
    {
        if(AnimationProgress3s < 2.70)
        {
            Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_2_Sprite);
        }
        else
        {
            if(AnimationProgress3s < 2.8)
            {
                Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_3_Sprite);
            }
            else
            {
                if(AnimationProgress3s < 2.85)
                {
                    Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_2_Sprite);
                }
                else
                {
                    Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_1_Sprite);
                }
            }
        }
    }
}

// This automatically slides between the Current X and the Target X
// Remember X and Y are assigned when the state ends, incase its "Interupted"
void AWapnSchemaPawn::AnimateWapnMove()
{
    if(Wapn_Eye_Sprite_Comp->GetSprite() != Wapn_Idle_Eye_2_Sprite)
    {
        Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_2_Sprite);
    }
    
    float AnimationProgress = (1.0/5.0) * (GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime);
    FVector TargetLocation = GenerateDefaultPosition(TargetTileX, TargetTileY);
    FVector StartingLocation = GenerateDefaultPosition(X, Y);
    FVector PanelDistance = TargetLocation - StartingLocation;
    PanelDistance = PanelDistance * AnimationProgress;
    StartingLocation.AddBounded(PanelDistance);
    SetActorLocation(StartingLocation);
}
// This will be a diagnal jump, so extra compatablility is not required
void AWapnSchemaPawn::AnimateWapnAttack()
{

    float AnimationProgress = (1.0/0.3) * (GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime);
    FVector TargetLocation = GenerateDefaultPosition(TargetTileX, TargetTileY);
    FVector StartingLocation = GenerateDefaultPosition(X, Y);
    FVector PanelDistance = TargetLocation - StartingLocation;
    PanelDistance = PanelDistance * AnimationProgress;
    StartingLocation.AddBounded(PanelDistance);
    float HeightAddition = 200 * FMath::Sin(AnimationProgress * PI);
    StartingLocation.Z += HeightAddition;
    SetActorLocation(StartingLocation);
    
    
}
void AWapnSchemaPawn::AnimateWapnHurt()
{
    float AnimationProgress = (1.0/2.0) * (GameState->GetServerWorldTimeSeconds() - SchemaStateStartTime);
    
    if(AnimationProgress < 0.3)
    {
        Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Hurt_Eye_1_Sprite);
    }
    else {
        if(AnimationProgress < 0.8)
        {
            Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Hurt_Eye_2_Sprite);
        }
        else {
            if(AnimationProgress < 0.9)
            {
                Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Hurt_Eye_1_Sprite);
            }
            else {
                Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Idle_Eye_1_Sprite);
            }
        }
    }
    // Wapn_Eye_Hurt_2_Sprite
    // Should be a jerk back animation
}
void AWapnSchemaPawn::AnimateWapnDying()
{
    Wapn_Eye_Sprite_Comp->SetSprite(Wapn_Hurt_Eye_1_Sprite);
    FVector v = GetActorLocation();
    v.Z -= 1.0;
    SetActorLocation(v);
    // A Disolving Animation?
}



// This happens on Attack, on Movement Fail, on end of world, Ect. Thusly it re-does any states and clears markings
// It also relocates the Wapn only on ATK configuration, as DEF and Special automatically proccess theirs
void AWapnSchemaPawn::Relocate() {
    
    ClearMarkingStatuses();
    SchemaState = ESchemaStateEnum::SSE_WAPN_ATK_IDLE;
    SchemaStateStartTime = GameState->GetServerWorldTimeSeconds();
    
    TArray<ABattleTileActor*> Tiles;
    switch((uint8)SchemaTeam)
    {
        case ((uint8)ETeamEnum::TTE_WHITE):
            Tiles = GameState->GetLeftMostTiles();
            break;
        case ((uint8)ETeamEnum::TTE_BLACK):
            Tiles = GameState->GetRightMostTiles();
            break;
    }
    
    if(Tiles.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ERROR! There should be a leftmost tile! Tiles Removed? Check!"));
    }
    
    
    bool Safe = false;
    for (auto& Tile : Tiles)
    {
        if(!Safe)
        {
            Safe = Tile->IsHabitable();
        }
    }
    if(Safe)
    {
        if(Tiles.Num() == 1)
        {
            X = Tiles[0]->X;
            Y = Tiles[0]->Y;
            SetActorLocation(GenerateDefaultPosition());
            GameState->ClearOwnerShip(this);
            PossesTile(X, Y);
            
        }
        else
        {
            ABattleTileActor* Tile;
            while(true)
            {
                Tile = Tiles[FMath::RandRange(0, Tiles.Num() - 1)];
                if(Tile->IsHabitable() )
                {
                    break;
                }
                
            }
            X = Tile->X;
            Y = Tile->Y;
            SetActorLocation(GenerateDefaultPosition());
            GameState->ClearOwnerShip(this);
            PossesTile(X, Y);
        }
    }
    
    
    
}

// Used to clear temporary status's used to mark temporary information
void AWapnSchemaPawn::ClearMarkingStatuses()
{
    SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK);
    SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_1);
    SchemaStatuses.Remove(ESchemaStatusEnum::SSE2_WAPN_COMPLETED_MOVE_CHECK_2);
    SchemaStatuses.Remove(ESchemaStatusEnum::SEE2_WAPN_DOUBLESTEP);
}

/*
 This Method will
 Return True if there is a valid path
 Return False if there is nothing done, and will also relocate the Pawn somewhere else
 
 It will not posses the valid path tile incase something interupts the movement
 */
bool AWapnSchemaPawn::GenerateAttackPath()
{
    
    int8 Direction;
    switch((uint8)SchemaTeam)
    {
        case ((uint8)ETeamEnum::TTE_WHITE):
            Direction = 1;
            break;
        case ((uint8)ETeamEnum::TTE_BLACK):
            Direction = -1;
            break;
            
    }
    // Check if TopRight is valid for Attacking
    if (GameState->ContainsTile(X + Direction, Y + 1))
    {
        ABattleTileActor* Tile = GameState->GetTile(X + Direction, Y + 1);
        if (Tile->AnyEnemiesOnTile(SchemaTeam))
        {
            TargetTileX = Tile->X;
            TargetTileY = Tile->Y;
            Attacking = true;
            DoubleStep = false;
            return true;
        }
        
    }
    // Checking if Bottem Right is valid for Attacking
    if (GameState->ContainsTile(X + Direction, Y - 1))
    {
        ABattleTileActor* Tile = GameState->GetTile(X + Direction, Y - 1);
        if (Tile->AnyEnemiesOnTile(SchemaTeam))
        {
            TargetTileX = Tile->X;
            TargetTileY = Tile->Y;
            Attacking = true;
            DoubleStep = false;
            return true;
        }
    }
    // Check if the Double Step is valid
    if (GameState->ContainsTile(X + Direction + Direction, Y) && GameState->ContainsTile(X + Direction, Y))
    {
        ABattleTileActor* Tile2 = GameState->GetTile(X + Direction + Direction, Y);
        ABattleTileActor* Tile1 = GameState->GetTile(X + Direction, Y);
        
        if (DoubleStep && Tile2->IsHabitable() && Tile1->IsHabitable())
        {
            TargetTileX = Tile2->X;
            TargetTileY = Tile2->Y;
            if(DoubleStep)
            {
                SchemaStatuses.Add(ESchemaStatusEnum::SEE2_WAPN_DOUBLESTEP);
            }
            Attacking = false;
            DoubleStep = false;
            return true;
        }
        
    }
    // Check if Forward is valid
    if (GameState->ContainsTile(X + Direction, Y))
    {
        ABattleTileActor* Tile = GameState->GetTile(X + Direction, Y);
        if (Tile->IsHabitable())
        {
            TargetTileX = Tile->X;
            TargetTileY = Tile->Y;
            Attacking = false;
            DoubleStep = false;
            return true;
        }
        
    }

    Relocate();
    return false;
}
bool AWapnSchemaPawn::GenerateDefendPath()
{
    return true;
}
bool AWapnSchemaPawn::GenerateSupportPath()
{
    return true;
}



