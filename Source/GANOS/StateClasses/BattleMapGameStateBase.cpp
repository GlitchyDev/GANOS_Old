// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "BattleMapGameStateBase.h"



ABattleMapGameStateBase::ABattleMapGameStateBase()
{
    
}

void ABattleMapGameStateBase::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> CollectedTileActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattleTileActor::StaticClass(), CollectedTileActors);
    for (auto& Actor : CollectedTileActors)
    {
        ABattleTileActor* TileActor = Cast<ABattleTileActor>(Actor);
        UE_LOG(LogTemp, Warning, TEXT("Added Tile X:%d Y:%d"), TileActor->X,TileActor->Y);
        TileArray.Add(TileActor);
    }
    
    TArray<AActor*> CollectedSchemaPawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseSchemaPawn::StaticClass(), CollectedSchemaPawns);
    for (auto& Actor : CollectedSchemaPawns)
    {
        ABaseSchemaPawn* SchemaPawn = Cast<ABaseSchemaPawn>(Actor);
        UE_LOG(LogTemp, Warning, TEXT("Added Schema Pawn %s"), *SchemaPawn->DisplayName);
        SchemaArray.Add(SchemaPawn);
    }
    
    LeftMostPanelX = -1;
    for (auto& Tile : TileArray)
    {
        if (LeftMostPanelX > Tile->X || LeftMostPanelX == -1)
        {
            LeftMostPanelX = Tile->X;
        }
    }
    int8 RightMostPanelX = -1;
    for (auto& Tile : TileArray)
    {
        if (RightMostPanelX < Tile->X || RightMostPanelX == -1)
        {
            RightMostPanelX = Tile->X;
        }
    }
    
    
}

// Called every frame
void ABattleMapGameStateBase::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
}



bool ABattleMapGameStateBase::ContainsTile(uint8 X, uint8 Y)
{
    
    for (auto& Tile : TileArray)
    {
        if (X == Tile->X && Y == Tile->Y)
        {
            return true;
        }
    }
    return false;
}
ABattleTileActor* ABattleMapGameStateBase::GetTile(uint8 X, uint8 Y)
{
    for (auto& Tile : TileArray)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Req %d %d"), X,Y);
        //UE_LOG(LogTemp, Warning, TEXT("Rec %d %d"), Tile->X,Tile->Y);
        
        
        if (X == Tile->X && Y == Tile->Y)
        {
            //UE_LOG(LogTemp, Warning, TEXT("Tile Found!"));
            
            return Tile;
        }
    }
    //UE_LOG(LogTemp, Warning, TEXT("Tile NULL!"));
    return NULL;
}
ABattleTileActor* ABattleMapGameStateBase::GetRandomTile()
{
    return TileArray[FMath::RandRange(0, TileArray.Num() - 1)];
}

TArray<ABattleTileActor*> ABattleMapGameStateBase::GetLeftMostTiles()
{
    TArray<ABattleTileActor*> LeftMostTiles;
    int8 LowestX = -1;
    for (auto& Tile : TileArray)
    {
        if (LowestX > Tile->X || LowestX == -1)
        {
            LowestX = Tile->X;
        }
    }
    for (auto& Tile : TileArray)
    {
        if (LowestX == Tile->X)
        {
            LeftMostTiles.Add(Tile);
        }
    }
    return LeftMostTiles;
}

TArray<ABattleTileActor*> ABattleMapGameStateBase::GetRightMostTiles()
{
    TArray<ABattleTileActor*> RightMostTiles;
    int8 HighestX = -1;
    for (auto& Tile : TileArray)
    {
        if (HighestX < Tile->X || HighestX == -1)
        {
            HighestX = Tile->X;
        }
    }
    for (auto& Tile : TileArray)
    {
        if (HighestX == Tile->X)
        {
            RightMostTiles.Add(Tile);
        }
    }
    return RightMostTiles;
}

void ABattleMapGameStateBase::ClearOwnerShip(ABaseSchemaPawn* Schema)
{
    for (auto& Tile : TileArray)
    {
        Tile->CurrentSchemas.Remove(Schema);
        Tile->Occupied = false;
    }
}
