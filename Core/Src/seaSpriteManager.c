#include "seaSpriteManager.h"

seaStructManager_t* seaStruct_Manager_new(int screenWidth,int screenHeight){

    seaStructManager_t* seaStructManager = calloc(1, sizeof(seaStructManager_t)); //Allocation of a sea sprite manager in memory

    seaStructManager->next_Island_Timer = 0.0f; //timer before next island spawn
 
    seaStructManager->seaPixelWidth = 30;
    seaStructManager->seaPixelHeight = 30;

    seaStructManager->screenWidth = screenWidth;
    seaStructManager->screenHeight = screenHeight + (seaStructManager->seaPixelHeight * 10); //Height is a little bit more since it used to "mask" the island spawn

    seaStructManager->seaTilesX = seaStructManager->screenWidth / seaStructManager->seaPixelWidth;
    seaStructManager->seaTilesY = seaStructManager->screenHeight / seaStructManager->seaPixelHeight;
    
    seaStructManager->count = (seaStructManager->seaTilesX * seaStructManager->seaTilesY); //Count of all the sea pixels needed for the screen to be full of them
    
    seaStructManager->seaSprites = calloc(seaStructManager->count, sizeof(seaSprite_t));//Allocation of n-count sea sprites in memory

    //Variables needed for island spawn
    seaStructManager->deltatime = GetFrameTime();
    seaStructManager->isFirst = true;
    seaStructManager->index = -20;

    PopulateSeaSpriteManagerArray(seaStructManager);
    SpawnSeaSprite(seaStructManager);

    return seaStructManager;
}

void SpawnSeaSprite(seaStructManager_t* seaStructManager){
    int counterY = -10;
    int counterX = 0;
    for(int i = 0; i < seaStructManager->count; i++) {
        
            counterX = i % seaStructManager->seaTilesX;

            seaStructManager->seaSprites[i]->position.x = counterX * seaStructManager->seaPixelWidth;
            seaStructManager->seaSprites[i]->position.y = counterY * seaStructManager->seaPixelHeight;
           

        if(i % seaStructManager->seaTilesX == 0){
            counterY++;
        }
    }
}

void SpawnIsland(seaStructManager_t* seaStructManager, int index){
    //If index is not changed an error occured so the function doesn't do anything
    if (index == -20){
        return;
    }
    //get a random index on the same x as the one selected before
    int RandomSpawnX = GetRandomValue(index, index + seaStructManager->seaTilesX-4);
    //random island
    int RandomSpawnSprite = GetRandomValue(0,2);

    //In every case 3 more sea sprites are needed since with only one the island is way too small and this cannot be fixed by using a bigger offset
    switch(RandomSpawnSprite)
    {
        case 0:
            seaStructManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){105,500};
            seaStructManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){105 + seaStructManager->seaPixelWidth,500};
            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasPosition = (Vector2){105 ,500 + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasPosition = (Vector2){105 + seaStructManager->seaPixelWidth,500  + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
        case 1:
            seaStructManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){170,500};
            seaStructManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){170 + seaStructManager->seaPixelWidth,500};
            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasPosition = (Vector2){170 ,500 + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasPosition = (Vector2){170 + seaStructManager->seaPixelWidth,500  + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
        case 2:
            seaStructManager->seaSprites[RandomSpawnX]->AtlasPosition = (Vector2){235,500};
            seaStructManager->seaSprites[RandomSpawnX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasPosition = (Vector2){235 + seaStructManager->seaPixelWidth,500};
            seaStructManager->seaSprites[RandomSpawnX + 1]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasPosition = (Vector2){235 ,500 + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX]->AtlasOffset = (Vector2){32,32};

            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasPosition = (Vector2){235 + seaStructManager->seaPixelWidth,500  + seaStructManager->seaPixelHeight};
            seaStructManager->seaSprites[RandomSpawnX + seaStructManager->seaTilesX + 1]->AtlasOffset = (Vector2){32,32};
            break;
    }

    
    
}

void PopulateSeaSpriteManagerArray(seaStructManager_t* seaStructManager){
    for (int i = 0; i < seaStructManager->count; i++) {
        seaStructManager->seaSprites[i] = seaSprite_new();
        seaStructManager->seaSprites[i]->position.x = -100;
        seaStructManager->seaSprites[i]->position.y = -100;
    }
   
}

void DrawSeaSpriteManager(seaStructManager_t* seaStructManager, Texture2D spritesheet)
{
    for(int i = 0; i < seaStructManager->count; i++) 
    {
        Rectangle source = (Rectangle){seaStructManager->seaSprites[i]->AtlasPosition.x, seaStructManager->seaSprites[i]->AtlasPosition.y, seaStructManager->seaSprites[i]->AtlasOffset.x, seaStructManager->seaSprites[i]->AtlasOffset.y}; //269, 369
        Rectangle dest = (Rectangle){seaStructManager->seaSprites[i]->position.x , seaStructManager->seaSprites[i]->position.y ,
                                     seaStructManager->seaSprites[i]->AtlasOffset.x, seaStructManager->seaSprites[i]->AtlasOffset.y};  //(float)GetScreenWidth(), (float)GetScreenHeight()
                
        Vector2 orig = (Vector2){0};
        DrawTexturePro(spritesheet, source, dest, orig ,0, WHITE);
        
    }
    
}

void UpdateSeaSpriteManager(seaStructManager_t* seaStructManager)
{
    seaStructManager->isFirst = true;
    for (int i = 0 ; i < seaStructManager->count; i ++)
    {
        seaStructManager->seaSprites[i]->position.y += seaStructManager->seaPixelHeight * seaStructManager->deltatime;
        //If they reach the bottom of the screen they are sent back to the very top (offscreen)
        if (seaStructManager->seaSprites[i]->position.y > GetScreenHeight()) 
        {
            seaStructManager->seaSprites[i]->position.y = -seaStructManager->seaPixelHeight * 10;

            seaStructManager->seaSprites[i]->AtlasPosition = (Vector2){269, 204};

            seaStructManager->seaSprites[i]->AtlasOffset = (Vector2){30,30};

            if(seaStructManager->isFirst)
            {
                //gets the index of the first sea sprite which is now on the upper end of the screen and is used later to determine island spawn location
                seaStructManager->isFirst= false;
                seaStructManager->index = i;
            }
        }
    }
    
    seaStructManager->next_Island_Timer += seaStructManager->deltatime;
    //Next island spawn
    if (seaStructManager->next_Island_Timer > 7)
    {
        seaStructManager->next_Island_Timer = 0;
        SpawnIsland(seaStructManager, seaStructManager->index);
    }
}

//Free the memory occupied by the manager and respective sea sprites at the end of program
void FreeSeaSpriteManager(seaStructManager_t* seaStructManager){
    for(int x = 0; x < seaStructManager->seaTilesX; x++) {
        for (int y = -1; y <= seaStructManager->seaTilesY; y++) 
        {
            FreeSeaSprite(seaStructManager->seaSprites[(y * seaStructManager->seaTilesX) + x]);
        }
    }
}