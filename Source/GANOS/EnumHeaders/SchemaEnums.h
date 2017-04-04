//
//  SchemaEnums.h
//  GANOS
//
//  Created by Robert Hannah on 3/17/17.
//  Copyright © 2017 Epic Games, Inc. All rights reserved.
//


#pragma once

UENUM(BlueprintType)
enum class ETeamEnum : uint8
{
    TTE_WHITE,
    TTE_BLACK
};

UENUM(BlueprintType)
enum class ETileStatusEnum : uint8
{
    TSE_DEBUG,
    TSE_HOLE,
};

UENUM(BlueprintType)
enum class ESchemaTypeEnum : uint8
{
    STE_BASE,
    STE_INKGTH,
    STE_WAPN,
    
};

// Status VS State    ( You have have one state but many Status's )
UENUM(BlueprintType)
enum class ESchemaStateEnum : uint8
{
    SSE_INKGTH_IDLE,
    SSE_INKGTH_ATTACK,
    SSE_INKGTH_DAMAGED,
    SSE_INKGTH_DYING,
    
    SSE_WAPN_ATK_IDLE,
    SSE_WAPN_ATK_MOVE,
    SSE_WAPN_ATK_ATTACK,
    SSE_WAPN_DEF_IDLE,
    SSE_WAPN_DEF_ATTACK,
    SSE_WAPN_SUP_IDLE,
    SSE_WAPN_SUP_ATTACK,
    SSE_WAPN_DAMAGED,
    SSE_WAPN_DYING,
    
    
    SSE_DUMMY,
};
UENUM(BlueprintType)
enum class ESchemaStatusEnum : uint8
{
    SSE2_WAPN_COMPLETED_MOVE_CHECK,
    SSE2_WAPN_COMPLETED_MOVE_CHECK_1,
    SSE2_WAPN_COMPLETED_MOVE_CHECK_2,
    SEE2_WAPN_DOUBLESTEP,
};

UENUM(BlueprintType)
enum class EDamageTypeEnum : uint8
{
    DTE_DEBUG
};

UENUM(BlueprintType)
enum class ESchemaBattleConfigurationEnum : uint8
{
    BTE_ATTACK,
    BTE_DEFEND,
    BTE_SUPPORT,
    BTE_GLITCH
};

UENUM(BlueprintType)
enum class EGANOSNetworkRoleEnum : uint8
{
    GNRE_LOGIC_ONLY,
    GNRE_ANIMATE_ONLY,
    GNRE_ANIMATE_AND_LOGIC
};


#ifndef SchemaEnums_h
#define SchemaEnums_h


#endif /* SchemaEnums_h */
