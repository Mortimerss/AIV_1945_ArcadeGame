#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "seaSprite.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "UIManager.h"
#include "seaSpriteManager.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{   
    InitAudioDevice();
    static int screenWidth = 640;
    static int screenHeight = 480;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    UIScreen_t* UI_Screen = UIScreen_new(screenWidth,screenHeight);

    seaStructManager_t* seaStructManager = seaStruct_Manager_new(screenWidth,screenHeight);
    
    BulletManager_t* bulletManager = BulletManager_new();

    playerStruct_t* playerSprite = playerStruct_new(bulletManager,UI_Screen);

    EnemiesContainer_t* enemiesContainer = EnemiesContainer_new(bulletManager,UI_Screen);

    Collision_Manager_t* collisionManager = Collision_manager_new(playerSprite,enemiesContainer,bulletManager);

    const char* app_dir = GetApplicationDirectory();
    TraceLog(LOG_INFO, "Bin directory: %s", app_dir);
    ChangeDirectory(app_dir);


    Music music = LoadMusicStream("assets/audio/background.mp3");
    music.looping = true;
    PlayMusicStream(music);

    Texture2D spritesheet = LoadTexture("assets/1945_atlas.bmp");
    if (spritesheet.id == 0) {
        TraceLog(LOG_ERROR, "Error loading atlas!");
        exit(-1);
    }


    char title[100];
    while (!WindowShouldClose()) 
    {   
        float delta_time = GetFrameTime();
        int fps = GetFPS();
        sprintf(title, "Delta: %.4f - FPS: %d", delta_time, fps);
        SetWindowTitle(title);

        static float time = 0;
        time += delta_time;
        unsigned char r = (unsigned char) ((sin(time) * 0.5f + 0.5f) * 255);

        UpdateSeaSpriteManager(seaStructManager);

        UpdatePlayer(playerSprite);

        UpdateEnemiesManager(enemiesContainer);

        UpdateBullets(bulletManager);
       
        CheckCollisions(collisionManager);

        UpdateMusicStream(music);

        BeginDrawing();

            ClearBackground(BLACK);

            DrawSeaSpriteManager(seaStructManager, spritesheet);

            DrawPlayer(playerSprite,spritesheet);

            DrawsEnemiesManager(enemiesContainer, spritesheet);

            DrawBulletManager(bulletManager, spritesheet);

            DrawUI(UI_Screen,spritesheet);
        
        EndDrawing();
    }

    UnloadMusicStream(music);
    UnloadTexture(spritesheet);
    FreeSeaSpriteManager(seaStructManager);
    FreeEnemyManager(enemiesContainer);
    FreePlayer(playerSprite);
    FreeBullets(bulletManager);
    FreeCollisionManager(collisionManager);
    FreeUI(UI_Screen);
    CloseWindow();

    return 0;
}