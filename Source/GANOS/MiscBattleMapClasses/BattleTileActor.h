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


    UPaperSpriteComponent* Inner_Sprite_Comp;
    UPaperSpriteComponent* Outer_Sprite_Comp;
    UPaperSpriteComponent* Ridge_Sprite_Comp;
    UPaperSpriteComponent* Left_Side_Sprite_Comp;
    UPaperSpriteComponent* Right_Side_Sprite_Comp;
    UPaperSprite* Inner_Sprite;
    UPaperSprite* Outer_Sprite;
    UPaperSprite* Ridge_Sprite;
    UPaperSprite* Side_Sprite;
    UPaperSprite* Side_Sprite_Revised;
	
	
};
