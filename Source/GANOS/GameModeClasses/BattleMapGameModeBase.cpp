// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "BattleMapGameModeBase.h"
#include "StateClasses/BattleMapPlayerState.h"
#include "StateClasses/BattleMapGameStateBase.h"
#include "ControllerClasses/BattleMapPlayerController.h"




ABattleMapGameModeBase::ABattleMapGameModeBase()
{
    PlayerStateClass = ABattleMapPlayerState::StaticClass();
    GameStateClass = ABattleMapGameStateBase::StaticClass();
    PlayerControllerClass = ABattleMapPlayerController::StaticClass();
    DefaultPawnClass = NULL;
    bUseSeamlessTravel = true;
}

