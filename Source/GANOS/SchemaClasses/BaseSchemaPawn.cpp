// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "BaseSchemaPawn.h"
#include "StateClasses/BattleMapGameStateBase.h"
#include "MiscBattleMapClasses/BattleTileActor.h"
#include "Core.h"
#include "UnrealNetwork.h"


DEFINE_LOG_CATEGORY(BaseSchemaLog);


ABaseSchemaPawn::ABaseSchemaPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    bAllowTickBeforeBeginPlay = false;
    bReplicates = true;
    bAlwaysRelevant = true;
    bReplicateMovement = false;
}


void ABaseSchemaPawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    DOREPLIFETIME(ABaseSchemaPawn, DisplayName);
    DOREPLIFETIME(ABaseSchemaPawn, MaxHealth);
    DOREPLIFETIME(ABaseSchemaPawn, CurrentHealth);
    DOREPLIFETIME(ABaseSchemaPawn, X);
    DOREPLIFETIME(ABaseSchemaPawn, Y);
    DOREPLIFETIME(ABaseSchemaPawn, SchemaType);
    DOREPLIFETIME(ABaseSchemaPawn, SchemaConfigurationType);
    DOREPLIFETIME(ABaseSchemaPawn, SchemaState);
    DOREPLIFETIME(ABaseSchemaPawn, SchemaStateStartTime);
    DOREPLIFETIME(ABaseSchemaPawn, SchemaStatuses);
    
}
// This is where any Variable that is replicated needs to go ._.





void ABaseSchemaPawn::DealDamage(ABaseSchemaPawn* Schema)
{
    // Upper Classes implement this
}
void ABaseSchemaPawn::RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount)
{
    // Upper Classes implement this
}

void ABaseSchemaPawn::BeginPlay()
{
    Super::BeginPlay();
    // Grabbing the Gamestate for future use
    GameState = Cast<ABattleMapGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
    
}

void ABaseSchemaPawn::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    SchemaTick(DeltaTime);
}

void ABaseSchemaPawn::SchemaTick(float DeltaSeconds)
{
}


void ABaseSchemaPawn::PossesTile(uint8 X, uint8 Y)
{
    ABattleTileActor* Tile = GameState->GetTile(X,Y);
    Tile->CurrentSchemas.Add(this);
    Tile->Occupied = true;
}

void ABaseSchemaPawn::UnpossesTile(uint8 X, uint8 Y)
{
    ABattleTileActor* Tile = GameState->GetTile(X,Y);
    Tile->CurrentSchemas.Remove(this);
    if(Tile->CurrentSchemas.Num() == 0)
    {
        Tile->Occupied = false;
    }
}

FVector ABaseSchemaPawn::GenerateDefaultPosition()
{
    // In the future we need to get the "True Center" for each map
    // We would grab the tiles true possition but it can't be determined if the Gamestate has properly loaded in the Tile Actors
    return GameState->GetTile(X,Y)->GetActorLocation();
}
FVector ABaseSchemaPawn::GenerateDefaultPosition(uint8 X, uint8 Y)
{
    return GameState->GetTile(X,Y)->GetActorLocation();
}

void ABaseSchemaPawn::OnRep_MaxHealth()
{
    UpdateHealthBar();
}
void ABaseSchemaPawn::OnRep_CurrentHealth()
{
    UpdateHealthBar();
}
void ABaseSchemaPawn::OnRep_DisplayName()
{
    UpdateNameTag();
}

void ABaseSchemaPawn::UpdateHealthBar()
{
    
}
void ABaseSchemaPawn::UpdateNameTag()
{
    
}


void ABaseSchemaPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
}

EGANOSNetworkRoleEnum ABaseSchemaPawn::DetermineNetworkRole()
{
    switch((uint8)GetNetMode())
    {
        case (uint8)ENetMode::NM_Standalone:
            return EGANOSNetworkRoleEnum::GNRE_ANIMATE_AND_LOGIC;
            break;
        case (uint8)ENetMode::NM_ListenServer:
            return EGANOSNetworkRoleEnum::GNRE_ANIMATE_AND_LOGIC;
            break;
        case (uint8)ENetMode::NM_Client:
            return EGANOSNetworkRoleEnum::GNRE_ANIMATE_ONLY;
            break;
        case (uint8)ENetMode::NM_DedicatedServer:
            return EGANOSNetworkRoleEnum::GNRE_LOGIC_ONLY;
            break;
        default:
            return EGANOSNetworkRoleEnum::GNRE_ANIMATE_AND_LOGIC;
            break;
    }
}
