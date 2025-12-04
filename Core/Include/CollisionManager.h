#ifndef COLLISION_MANAGER_C
#define COLLISION_MANAGER_C
#include "EnemyManager.h"
#include "Player.h"
#include "BulletManager.h"

typedef struct Collision_Manager_t
{
    playerStruct_t* playerReference;
    EnemiesContainer_t* enemiesReferences;
    BulletManager_t* bulletsReferences;
    
    

}Collision_Manager_t;

Collision_Manager_t* Collision_manager_new(playerStruct_t* player,EnemiesContainer_t* enemiesReferences,BulletManager_t* bullets);

void CheckCollisions(Collision_Manager_t* collisionManager);

void FreeCollisionManager(Collision_Manager_t* collisionManager);

#endif