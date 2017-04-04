// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "MiscBattleMapClasses/BattleTileActor.h"
#include "SchemaClasses/BaseSchemaPawn.h"
#include "BattleMapGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GANOS_API ABattleMapGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    TArray<class ABattleTileActor*> TileArray;
    TArray<class ABaseSchemaPawn*> SchemaArray;
    int8 LeftMostPanelX;
    int8 RightMostPanelX;
    
    void ClearOwnerShip(ABaseSchemaPawn* Schema);
    
    
    
    ABattleMapGameStateBase();
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaSeconds ) override;
    
    bool ContainsTile(uint8 x,uint8);
    ABattleTileActor* GetTile(uint8 X, uint8 Y);
    ABattleTileActor* GetRandomTile();
    TArray<ABattleTileActor*> GetLeftMostTiles();
    TArray<ABattleTileActor*> GetRightMostTiles();
	
	
};
