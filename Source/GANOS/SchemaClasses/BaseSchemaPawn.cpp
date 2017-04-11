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
    // Clients will simulate their own movement
}

// Required for use Methods

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





void ABaseSchemaPawn::DealDamage(ABaseSchemaPawn* Schema)
{
    // Sub Classes implement this
}
void ABaseSchemaPawn::RecieveDamage(ABaseSchemaPawn* Attacker, EDamageTypeEnum Type, uint8 DamageAmount)
{
    // Sub Classes implement this
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
    // Sub Classes implement this
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
    return GameState->GetTile(X,Y)->GetActorLocation();
}
FVector ABaseSchemaPawn::GenerateDefaultPosition(uint8 X, uint8 Y)
{
    return GameState->GetTile(X,Y)->GetActorLocation();
}

// On Replication Functions
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
// Functions implemented by upper classes due to the UE4 bug where components can't be
// Added from Child Classes to Super class Components
void ABaseSchemaPawn::UpdateHealthBar()
{
    
}
void ABaseSchemaPawn::UpdateNameTag()
{
    
}

// Player specific Methos

void ABaseSchemaPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);
}

// Misc Methods that should be moved
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
