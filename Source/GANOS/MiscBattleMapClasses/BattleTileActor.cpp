// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "BattleTileActor.h"
#include "StateClasses/BattleMapGameStateBase.h"
#include "SchemaClasses/BaseSchemaPawn.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "EnumHeaders/SchemaEnums.h"



// Sets default values

ABattleTileActor::ABattleTileActor()
{
    PrimaryActorTick.bCanEverTick = true;
    CreateTileVisual();
    //UpdateTileColor();
    //UE_LOG(LogTemp, Warning, TEXT("Reconstruct Color"));
    
    
}

void ABattleTileActor::OnConstruction(const FTransform & Transform)
{
    UpdateTileApperance();
    UE_LOG(LogTemp, Warning, TEXT("Reconstruct Color"));
}

bool ABattleTileActor::AnyEnemiesOnTile(ETeamEnum Team)
{
    if(CurrentSchemas.Num() == 0)
    {
        return false;
    }
    else
    {
        for (ABaseSchemaPawn* Schema : CurrentSchemas)
        {
            switch((uint8)Schema->SchemaTeam)
            {
                case ((uint8)ETeamEnum::TTE_BLACK):
                    switch((uint8)Team)
                {
                    case ((uint8)ETeamEnum::TTE_BLACK):
                        return false;
                        break;
                    case ((uint8)ETeamEnum::TTE_WHITE):
                        return true;
                        break;
                }
                    break;
                case ((uint8)ETeamEnum::TTE_WHITE):
                    switch((uint8)Team)
                {
                    case ((uint8)ETeamEnum::TTE_BLACK):
                        return true;
                        break;
                    case ((uint8)ETeamEnum::TTE_WHITE):
                        return false;
                        break;
                }
                    break;
            }
            
            /*
             if(  ETeamEnum::TTE_BLACK == Team )
             {
             return true;
             }
             */
        }
        return false;
    }
    
}

bool ABattleTileActor::IsHabitable()
{
    return (!this->TileStatuses.Contains(ETileStatusEnum::TSE_HOLE) && CurrentSchemas.Num() == 0);
    
}

void ABattleTileActor::UpdateTileApperance()
{
    
    switch((uint8)TileTeam)
    {
        case ((uint8)ETeamEnum::TTE_WHITE):
            Inner_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Outer_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Front_Ridge_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Back_Ridge_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Right_Side_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Left_Side_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Color White"));
            break;
        case ((uint8)ETeamEnum::TTE_BLACK):
            Inner_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            Outer_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            Front_Ridge_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            Back_Ridge_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            Right_Side_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            Left_Side_Sprite_Comp->SetSpriteColor(FColor(100,100,100));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Color Black"));
            break;
        default:
            Outer_Sprite_Comp->SetSpriteColor(FLinearColor(255,255,255));
            Front_Ridge_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Back_Ridge_Sprite_Comp->SetSpriteColor(FColor(255,255,255));
            Right_Side_Sprite_Comp->SetSpriteColor(FLinearColor(255,255,255));
            Left_Side_Sprite_Comp->SetSpriteColor(FLinearColor(255,255,255));
            UE_LOG(LogTemp, Warning, TEXT("Reconstruct Color Default"));
            break;
    }
    
    if (TileStatuses.Contains(ETileStatusEnum::TSE_HOLE))
    {
        Inner_Sprite_Comp->SetVisibility(false);
    }
    else
    {
        Inner_Sprite_Comp->SetVisibility(true);
    }
    
}




void ABattleTileActor::CreateTileVisual()
{
    
    UArrowComponent* Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    Arrow->SetVisibility(false);
    
    Inner_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Inner_Sprite_Comp"));
    Outer_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Outer_Sprite_Comp"));
    Front_Ridge_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Front_Ridge_Sprite_Comp"));
    Back_Ridge_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Back_Ridge_Sprite_Comp"));
    Left_Side_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Left_Side_Sprite_Comp"));
    Right_Side_Sprite_Comp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Right_Side_Sprite_Comp"));
    
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Paper2D/DefaultLitSpriteMaterial.DefaultLitSpriteMaterial'"));
    UMaterial* SpriteMaterial = (UMaterial*)Material.Object;
    
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Inner_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Tile/Panel_Inside_Sprite.Panel_Inside_Sprite'"));
    Inner_Sprite = Inner_SpriteObj.Object;
    Inner_Sprite_Comp->SetSprite(Inner_Sprite);
    Inner_Sprite_Comp->SetRelativeLocation(FVector(0,-0.1,-0.1));
    Inner_Sprite_Comp->SetRelativeRotation(FRotator(0,0,-45));
    Inner_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Outer_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Tile/Panel_Outer_Sprite.Panel_Outer_Sprite'"));
    Outer_Sprite = Outer_SpriteObj.Object;
    Outer_Sprite_Comp->SetSprite(Outer_Sprite);
    Outer_Sprite_Comp->SetRelativeLocation(FVector(0,0,0));
    Outer_Sprite_Comp->SetRelativeRotation(FRotator(0,0,-45));
    Outer_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Ridge_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Tile/Panel_Ridge_Sprite.Panel_Ridge_Sprite'"));
    Ridge_Sprite = Ridge_SpriteObj.Object;
    
    Front_Ridge_Sprite_Comp->SetSprite(Ridge_Sprite);
    Front_Ridge_Sprite_Comp->SetRelativeLocation(FVector(0,52,-75));
    Front_Ridge_Sprite_Comp->SetRelativeRotation(FRotator(0,0,0));
    Front_Ridge_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    Back_Ridge_Sprite_Comp->SetSprite(Ridge_Sprite);
    Back_Ridge_Sprite_Comp->SetRelativeLocation(FVector(0,-52,25));
    Back_Ridge_Sprite_Comp->SetRelativeRotation(FRotator(0,0,0));
    Back_Ridge_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    
    static ConstructorHelpers::FObjectFinder<UPaperSprite> Side_SpriteObj(TEXT("PaperSprite'/Game/GanosContent/Sprites/Tile/Panel_Side_Sprite.Panel_Side_Sprite'"));
    Side_Sprite = Side_SpriteObj.Object;
    Left_Side_Sprite_Comp->SetSprite(Side_Sprite);
    Left_Side_Sprite_Comp->SetRelativeLocation(FVector(-120,0,-25));
    Left_Side_Sprite_Comp->SetRelativeRotation(FRotator(0,90,0));
    Left_Side_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    Right_Side_Sprite_Comp->SetSprite(Side_Sprite);
    Right_Side_Sprite_Comp->SetRelativeLocation(FVector(120,0,-25));
    Right_Side_Sprite_Comp->SetRelativeRotation(FRotator(0,90,0));
    Right_Side_Sprite_Comp->SetMaterial(0, SpriteMaterial);
    
    
    RootComponent = Arrow;
    Inner_Sprite_Comp->AttachTo(RootComponent);
    Outer_Sprite_Comp->AttachTo(RootComponent);
    Front_Ridge_Sprite_Comp->AttachTo(RootComponent);
    Back_Ridge_Sprite_Comp->AttachTo(RootComponent);
    Left_Side_Sprite_Comp->AttachTo(RootComponent);
    Right_Side_Sprite_Comp->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ABattleTileActor::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ABattleTileActor::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}


