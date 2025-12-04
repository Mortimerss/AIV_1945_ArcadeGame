#ifndef seaSpriteManager_C
#define seaSpriteManager_C

#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "seaSprite.h"


typedef struct seaStructManager_t
{
    seaSprite_t** seaSprites;

    float next_Island_Timer;

    int seaPixelWidth ;
    int seaPixelHeight ;

    int screenWidth;
    int screenHeight;

    int seaTilesX ;
    int seaTilesY ; 

    int count;

    float timer;
    float deltatime;

    int index;
    bool isFirst;
    
}seaStructManager_t;

seaStructManager_t* seaStruct_Manager_new(int screenWidth,int screenHeight);

void SpawnSeaSprite(seaStructManager_t* seaSpriteManager);

void PopulateSeaSpriteManagerArray(seaStructManager_t* seaSpriteManager);

void DrawSeaSpriteManager(seaStructManager_t* seaSpriteManager, Texture2D spritesheet);

void UpdateSeaSpriteManager(seaStructManager_t* seaSpriteManager);

void FreeSeaSpriteManager(seaStructManager_t* seaSpriteManager);

void SpawnIsland(seaStructManager_t* seaSpriteManager, int index);

#endif