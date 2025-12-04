#include "BulletManager.h"
#include "raylib.h"

BulletManager_t* BulletManager_new(){
    BulletManager_t* bulletManager = calloc(1, sizeof(BulletManager_t)); //Allocation in memory of the bullet manager

    bulletManager->bulletCount = 25;

    bulletManager->enemyBullets = calloc(bulletManager->bulletCount, sizeof(BulletManager_t));//Allocation in memory of enemy bullets
    bulletManager->playerBullets = calloc(bulletManager->bulletCount, sizeof(BulletManager_t));//Allocation in memory of player bullets

    PopulateArray(bulletManager);

    return bulletManager;
}

//Function to populate the array with bullets
void PopulateArray(BulletManager_t* bulletManager) {
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        bulletManager->enemyBullets[i] = Bullet_new();
        bulletManager->enemyBullets[i]->isActive = false;
        bulletManager->enemyBullets[i]->position.x = -200;
        bulletManager->enemyBullets[i]->position.y = -200;
        bulletManager->playerBullets[i] = Bullet_new();
        bulletManager->playerBullets[i]->isActive = false;
        bulletManager->playerBullets[i]->position.x = -200;
        bulletManager->playerBullets[i]->position.y = -200;
    }
}

void ActivatePlayerBullet(BulletManager_t* bulletManager, Vector2 PlayerBulletPosition){
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        if (!bulletManager->playerBullets[i]->isActive) {
            PlayerBulletPosition = (Vector2){PlayerBulletPosition.x + bulletManager->playerBullets[i]->bulletPixelWidth * 0.5,PlayerBulletPosition.y};
            bulletManager->playerBullets[i]->isActive = true;
            bulletManager->playerBullets[i]->isPlayerBullet = true;
            bulletManager->playerBullets[i]->position = PlayerBulletPosition;
            GetCorrectFrame(bulletManager->playerBullets[i],(Vector2){0,1});
            break;
        }
    }
}

void ActivateEnemyBullet(BulletManager_t* bulletManager, Vector2 EnemyBulletPosition,Vector2 dir)
{
    for (int i = 0; i < bulletManager->bulletCount; i++) {
        if (!bulletManager->enemyBullets[i]->isActive) 
        {
            EnemyBulletPosition = (Vector2){EnemyBulletPosition.x + bulletManager->enemyBullets[i]->bulletPixelWidth * 0.5,EnemyBulletPosition.y};
            bulletManager->enemyBullets[i]->isActive = true;
            bulletManager->enemyBullets[i]->isPlayerBullet = false;
            bulletManager->enemyBullets[i]->position = EnemyBulletPosition;
            bulletManager->enemyBullets[i]->enemyBulletDirection = dir;
            GetCorrectFrame(bulletManager->enemyBullets[i],bulletManager->enemyBullets[i]->enemyBulletDirection);
            break;
        }   
    }
}

//Doing two for is not really ideal for the program, but if i tried to put them together it tended to bug out sometimes
void UpdateBullets(BulletManager_t* bulletManager){
    for (int i = 0; i < bulletManager->bulletCount; i++) 
    {
        UpdatePlayerBullet(bulletManager->playerBullets[i]);
        
    }
    for (int i = 0; i < bulletManager->bulletCount; i++) {

        UpdateEnemyBullet(bulletManager->enemyBullets[i]);
    }
}

void DrawBulletManager(BulletManager_t* bulletManager, Texture2D spritesheet){
    for (int i = 0; i < bulletManager->bulletCount; i++) {
       if (bulletManager->playerBullets[i]->isActive) {
            Rectangle source_bullet = (Rectangle){33, 165, bulletManager->playerBullets[i]->bulletPixelWidth, bulletManager->playerBullets[i]->bulletPixelHeight};
            Rectangle dest_bullet = (Rectangle){bulletManager->playerBullets[i]->position.x,bulletManager->playerBullets[i]->position.y, bulletManager->playerBullets[i]->bulletPixelWidth*0.5f,bulletManager->playerBullets[i]->bulletPixelHeight*0.5f};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_bullet = (Vector2){0};
            DrawTexturePro(spritesheet, source_bullet, dest_bullet, orig_bullet, 0, WHITE);

       }
       if (bulletManager->enemyBullets[i]->isActive) {
            Rectangle source_bullet = (Rectangle){((bulletManager->enemyBullets[i]->bulletPixelWidth  +1) * bulletManager->enemyBullets[i]->correctFrame), 235, bulletManager->enemyBullets[i]->bulletPixelWidth, bulletManager->enemyBullets[i]->bulletPixelHeight};
            Rectangle dest_bullet = (Rectangle){bulletManager->enemyBullets[i]->position.x,bulletManager->enemyBullets[i]->position.y, bulletManager->enemyBullets[i]->bulletPixelWidth*0.5f,bulletManager->enemyBullets[i]->bulletPixelHeight*0.5f};  //(float)GetScreenWidth(), (float)GetScreenHeight()
            Vector2 orig_bullet = (Vector2){0};
            DrawTexturePro(spritesheet, source_bullet, dest_bullet, orig_bullet, bulletManager->enemyBullets[i]->necessaryRotation, WHITE);
       }
    }      
}


//Free bullet manager memory and relative bullets after pressing esc to close the program
void FreeBullets(BulletManager_t* bulletManager)
{
    for (int i = 0; i < bulletManager->bulletCount; i++) 
    {
        FreeBullet(bulletManager->playerBullets[i]);
        FreeBullet(bulletManager->enemyBullets[i]);
    }
    free(bulletManager);
}