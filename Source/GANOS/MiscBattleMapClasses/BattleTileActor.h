// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "EnumHeaders/SchemaEnums.h"
#include "BattleTileActor.generated.h"



UCLASS()
class GANOS_API ABattleTileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABattleTileActor();
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    virtual void OnConstruction(const FTransform & Transform) override;
    
    
    void CreateTileVisual();
    void UpdateTileApperance();
    bool AnyEnemiesOnTile(ETeamEnum Team);
    bool IsHabitable();



    UPaperSpriteComponent* Inner_Sprite_Comp;
    UPaperSpriteComponent* Outer_Sprite_Comp;
    UPaperSpriteComponent* Front_Ridge_Sprite_Comp;
    UPaperSpriteComponent* Back_Ridge_Sprite_Comp;
    UPaperSpriteComponent* Left_Side_Sprite_Comp;
    UPaperSpriteComponent* Right_Side_Sprite_Comp;
    UPaperSprite* Inner_Sprite;
    UPaperSprite* Outer_Sprite;
    UPaperSprite* Ridge_Sprite;
    UPaperSprite* Side_Sprite;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 X;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    uint8 Y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    ETeamEnum TileTeam;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    TArray<ETileStatusEnum> TileStatuses;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    bool Occupied;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
    TArray<class ABaseSchemaPawn*> CurrentSchemas;
	
	
};
