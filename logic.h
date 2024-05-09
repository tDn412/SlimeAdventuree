#ifndef _LOGIC__H
#define _LOGIC__H

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "structs.h"

class Game {
public:
    Entity player;
    std::list<Entity*> bullets;
    std::list<Entity*> fighters;
    std::list<Entity*> obstacles;
    std::list<Entity*> explosions;
    std::list<Entity*> debris;
    std::list<Entity*> fireballs;
    Star stars[MAX_STARS];

    SDL_Texture *bulletTexture, *obstacleTexture, *obstacleBulletTexture, *background, *explosionTexture, *fireballTexture;
    int obstacleSpawnTimer;
    int fireballSpawnTimer;
    int stageResetTimer;

    int backgroundX = 0;

    Game(); // Constructor
    ~Game(); // Destructor

    void init(Graphics& graphics);
    void initPlayer(Entity& player);
    void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
    void reset();
    void empty(std::list<Entity*>& entities);
    void initStarfield();
    void fireBullet();
    void fireball();
    void fireObstacleBullet(Entity* obstacle);
    void doPlayer(int keyboard[]);
    bool bulletHitFighter(Entity* b);
    bool fireballHitFighter(Entity* b);
    void doBullets();
    void doObstacles();
    void doFireballs();
    void spawnObstacles();
    void spawnFireballs();
    void doFighters();
    void doBackground();
    void doStarfield();
    void doExplosions(Graphics& graphics);
    void doLogic(int keyboard[]);
    void drawBackground(SDL_Renderer* renderer);
    void drawStarfield(SDL_Renderer* renderer);
    void draw(Graphics& graphics);
    void quit(); // New function declaration
};

#endif // _LOGIC__H
