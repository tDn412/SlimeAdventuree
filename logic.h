#ifndef _LOGIC__H
#define _LOGIC__H

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "structs.h"

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
public:
    Game();
    ~Game();
    void init(Graphics& graphics);
    void reset();
    void doLogic(int keyboard[]);
    void draw(Graphics& graphics);
    void quit();
    void handleEvents(SDL_Event& event);

private:
    void initPlayer(Entity& player);
    void fireBullet();
    void fireball();
    void helicopter();
    void doHelicopter();
    void enemyfire(Entity* obstacle);
    void doPlayer(int keyboard[]);
    bool bulletHitFighter(Entity* bullet);
    bool fireballHitFighter(Entity* fireball);
    bool obstacleHitFighter(Entity* obstacle);
    void doBullets();
    void doFireballs();
    void doObstacles();
    void spawnHelicopter();
    void spawnObstacles();
    void spawnFireballs();
    void doBackground();
    void doStarfield();
    void drawBackground(SDL_Renderer* renderer);
    void drawMenu(SDL_Renderer* renderer);
    void drawStarfield(SDL_Renderer* renderer);

    GameState gameState;
    Entity player;
    std::list<Entity*> obstacles;
    std::list<Entity*> bullets;
    std::list<Entity*> fireballs;
    std::list<Entity*> helicopters;

    SDL_Texture* bulletTexture;
    SDL_Texture* obstacleTexture1;
    SDL_Texture* obstacleTexture2;
    SDL_Texture* obstacleTexture3;
    SDL_Texture* obstacleBulletTexture;
    SDL_Texture* background;
    SDL_Texture* explosionTexture;
    SDL_Texture* fireballTexture;
    SDL_Texture* menuTexture;
    SDL_Texture* resumeTexture1;
    SDL_Texture* resumeTexture2;
    SDL_Texture* playagainTexture1;
    SDL_Texture* playagainTexture2;
    SDL_Texture* quitTexture1;
    SDL_Texture* quitTexture2;
    SDL_Texture* helicopterTexture;

    SDL_Rect playButton;
    SDL_Rect scoreButton;
    SDL_Rect quitButton;
    SDL_Rect resumeButton;
    SDL_Rect playAgainButton;
    SDL_Rect quitGameButton;

    int backgroundX;
    int obstacleSpawnTimer;
    int fireballSpawnTimer;
    int helicopterSpawntimer;
    int stageResetTimer;

    Star stars[MAX_STARS];
};

#endif // _LOGIC__H
