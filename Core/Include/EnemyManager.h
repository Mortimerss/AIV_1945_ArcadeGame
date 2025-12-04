#ifndef ENEMY_MANAGER_C
#define ENEMY_MANAGER_C
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <Enemy.h>
#include "UIManager.h"


typedef struct EnemiesContainer_t
{
    enemySprite_t **enemies;
    BulletManager_t* bulletManagerRef;
    UIScreen_t* UI_ScreenRef;
    int enemyCount;
    float time; 

}EnemiesContainer_t;

EnemiesContainer_t* EnemiesContainer_new(BulletManager_t* bulletManagerRef,UIScreen_t* UI_ScreenRef);


void PopulateEnemiesContainer(EnemiesContainer_t* container,BulletManager_t* bulletManagerRef);

void SpawnEnemy(EnemiesContainer_t* container, float x, float y);

void UpdateEnemiesManager(EnemiesContainer_t* container);

void DrawsEnemiesManager(EnemiesContainer_t* enemyContainer, Texture2D spritesheet);

void ActivateEnemy(EnemiesContainer_t* container);

void FreeEnemyManager(EnemiesContainer_t* enemyContainer);

#endif
