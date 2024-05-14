#include "logic.h"
#include "defs.h"
#include "graphics.h"
#include "structs.h"
#include <iostream>

Game::Game() {
    // Constructor
}

Game::~Game() {
    // Destructor
}

void Game::init(Graphics& graphics) {
    player.texture = graphics.loadTexture("img/slime.png");
    SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
    bulletTexture = graphics.loadTexture("img/tinyBlackBox.png");
    obstacleTexture1 = graphics.loadTexture("img/small_metal_spike.png");
    obstacleTexture2 = graphics.loadTexture("img/small_wood_spike.png");
    obstacleTexture3 = graphics.loadTexture("img/long_wood_spike.png");
    obstacleBulletTexture = graphics.loadTexture("img/obstacleBullet.png");
    background = graphics.loadTexture("img/1920x1080.png");
    explosionTexture = graphics.loadTexture("img/pngegg.png");
    fireballTexture = graphics.loadTexture(FIREBALL_SPRITE_FILE);
    menuTexture = graphics.loadTexture("img/menu.png");
    resumeTexture1 = graphics.loadTexture("img/resumeTexture1.png");
    resumeTexture2 = graphics.loadTexture("img/resumeTexture2.png");
    playagainTexture1 = graphics.loadTexture("img/playagainTexture1");
    playagainTexture2 = graphics.loadTexture("img/playagainTexture2.png");
    quitTexture1 = graphics.loadTexture("img/quitTexture1.png");
    quitTexture2 = graphics.loadTexture("img/quitTexture2.png");
    helicopterTexture = graphics.loadTexture(HELICOPTER_SPRITE_FILE);
    reset();
}


void Game::initPlayer(Entity& player) {
    player.x = 100;
    player.y = FLOOR_Y - player.h;
    player.health = 10; // Khởi tạo máu của player là 10
    player.side = SIDE_PLAYER;
    player.reload = 0;
}

void Game::calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
    int steps = max(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }

    *dx = (x1 - x2) / static_cast<float>(steps);
    *dy = (y1 - y2) / static_cast<float>(steps);
}

void Game::reset() {
    empty(obstacles);
    empty(bullets);
    empty(fireballs);
    initPlayer(player);
    initStarfield();
    obstacleSpawnTimer = 0;
    fireballSpawnTimer = 0;
    helicopterSpawntimer = 0;
    stageResetTimer = FRAME_PER_SECOND * 3;
}

void Game::empty(std::list<Entity*>& entities) {
    while (!entities.empty()) {
        Entity* e = entities.front();
        entities.pop_front();
        if (e != &player) delete e;
    }
}

void Game::initStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_HEIGHT;
        stars[i].speed = 1 + rand() % 8;
    }
}

void Game::fireBullet() {
    Entity *bullet = new Entity();
    bullets.push_back(bullet);

    bullet->x = player.x;
    bullet->y = player.y;
    bullet->y += (player.h / 2) - (bullet->h / 2);
    bullet->dx = PLAYER_BULLET_SPEED;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = SIDE_PLAYER;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->reload = PLAYER_RELOAD;
}

void Game::fireball() {
    Entity* fireball = new Entity();
    fireball->initAnimation(fireballTexture, FIREBALL_FRAMES, FIREBALL_CLIPS);
    fireballs.push_back(fireball);
    fireball->x = rand() % (SCREEN_WIDTH - fireball->w); // Random vị trí theo chiều ngang
    fireball->y = -fireball->h; // Spawn từ trên trời xuống
    fireball->dy = gravity; // Fireball rơi xuống
    fireball->side = SIDE_ALIEN;
    fireball->reload = (rand() % FRAME_PER_SECOND * 2);
    SDL_QueryTexture(fireball->texture, NULL, NULL, &fireball->w, &fireball->h);
}

void Game::helicopter() {
    Entity* helicopter = new Entity();
    helicopter->initAnimation(helicopterTexture, HELICOPTER_FRAMES, HELICOPTER_CLIPS);
    helicopters.push_back(helicopter);
    helicopter->x = rand() % (SCREEN_WIDTH - helicopter->w); // Random vị trí theo chiều ngang
    helicopter->y = -helicopter->h; // Spawn từ trên trời xuống
    helicopter->dy = gravity; // Fireball rơi xuống
    helicopter->side = SIDE_ALIEN;
    helicopter->reload = (rand() % FRAME_PER_SECOND * 2);
    helicopter->bullet = 5;
    SDL_QueryTexture(helicopter->texture, NULL, NULL, &helicopter->w, &helicopter->h);
}

void Game::doHelicopter() {
    auto it = helicopters.begin();
    while (it != helicopters.end()) {
        auto temp = it++;
        Entity* helicopter = *temp;
        if(helicopter->reload > 0) helicopter->reload--;
        helicopter->move();
        if (helicopter->y >= 100) {
            helicopter->dy = -1;
        }
        if(helicopter->y <= -10){
            helicopters.erase(temp);
        }
    }
    for (Entity* e : helicopters) {
        if (player.health > 0 && e->reload <= 0)
            enemyfire(e);
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
/*
void Game::enemyfire(Entity* obstacle) {
    Entity *bullet = new Entity();
    bullets.push_back(bullet);
    bullet->x = obstacle->x;
    bullet->y = obstacle->y;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = SIDE_ALIEN;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (obstacle->w / 2) - (bullet->w / 2);
    bullet->y += (obstacle->h / 2) - (bullet->h / 2);

    calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
              obstacle->x, obstacle->y, &bullet->dx, &bullet->dy);
    bullet->dx *= OBSTACLE_BULLET_SPEED;
    bullet->dy *= OBSTACLE_BULLET_SPEED;

    obstacle->reload = (rand() % FRAME_PER_SECOND * 2);
}
*/

void Game::enemyfire(Entity* obstacle) {
    Entity *bullet = new Entity();
    bullets.push_back(bullet);
    bullet->x = obstacle->x;
    bullet->y = obstacle->y;
    bullet->health = 1;
    bullet->texture = bulletTexture;
    bullet->side = SIDE_ALIEN;
    SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

    bullet->x += (obstacle->w / 2) - (bullet->w / 2);
    bullet->y += (obstacle->h / 2) - (bullet->h / 2);

    calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
              obstacle->x, obstacle->y, &bullet->dx, &bullet->dy);
    bullet->dx *= OBSTACLE_BULLET_SPEED;
    bullet->dy *= OBSTACLE_BULLET_SPEED;

    obstacle->bullet--;
    obstacle->reload = (rand() % FRAME_PER_SECOND * 2);
}


void Game::doPlayer(int keyboard[]) {
    if (player.health <= 0) {
        return;
    }
    player.dx = 0;
    if (player.reload > 0) player.reload--;
    // Xử lý di chuyển
    if (keyboard[SDL_SCANCODE_UP]) player.Startjump();
    if (keyboard[SDL_SCANCODE_LEFT]) player.dx = -PLAYER_SPEED;
    if (keyboard[SDL_SCANCODE_RIGHT]) player.dx = PLAYER_SPEED;
    // Kiểm tra nếu không có phím nào được nhấn thì player dừng lại
    if (!keyboard[SDL_SCANCODE_UP]) player.Endjump();
    //if (!keyboard[SDL_SCANCODE_LEFT] && !keyboard[SDL_SCANCODE_RIGHT]) player.dx = 0;
    // Xử lý bắn đạn
    //if(player.reload > 0) player.reload--;
    //if (keyboard[SDL_SCANCODE_LCTRL] && player.reload == 0) fireBullet();
    // Di chuyển player dựa trên vận tốc đã thiết lập
    player.playermove();
    // Kiểm tra giới hạn màn hình
    if (player.x < 0) player.x = 0;
    else if (player.x >= SCREEN_WIDTH - player.w)
        player.x = SCREEN_WIDTH - player.w;
    if (player.y < 0) player.y = 0;
    else if (player.y >= SCREEN_HEIGHT - player.h)
        player.y = SCREEN_HEIGHT - player.h;
}

bool Game::bulletHitFighter(Entity* bullet) {
        if (player.side != bullet->side && bullet->collides(&player)) {
            player.health -= 10;
            return true;
        }
    return false;
}

bool Game::fireballHitFighter(Entity* fireball) {
    if (player.side != fireball->side && fireball->collides(&player)) {
        player.health -= 10;
        return true;
    }
    return false;
}

bool Game::obstacleHitFighter(Entity* obstacle) {
    if (player.side != obstacle->side && obstacle->collides(&player)) {
        player.health -= 10;
        return true;
    }
    return false;
}

void Game::doBullets() {
    auto it = bullets.begin();
    while (it != bullets.end()) {
        auto temp = it++;
        Entity* b = *temp;
        b->move();
        if (bulletHitFighter(b) || b->offScreen()) {
            delete b;
            bullets.erase(temp);
        }
    }
}

void Game::doFireballs() {
    auto it = fireballs.begin();
    while (it != fireballs.end()) {
        auto temp = it++;
        Entity* fireball = *temp;
        fireball->move();
        if (fireballHitFighter(fireball) || fireball->y >= FLOOR_Y) {
            delete fireball;
            fireballs.erase(temp);
        }
    }
}

void Game::doObstacles() {
        auto it = obstacles.begin();
        it++;
        while (it != obstacles.end()) {
            auto temp = it++;
            Entity* obstacle = *temp;
            obstacle->move();
            if(obstacleHitFighter(obstacle)) player.health = 0;
            if (obstacle->x < -obstacle->w) obstacle->health = 0;
            if (obstacle->health == 0) {
                delete obstacle;
                obstacles.erase(temp);
                continue;
            }
        }
}

void Game::spawnHelicopter() {
    if (--helicopterSpawntimer <= 0) {
        helicopter();
        helicopterSpawntimer = 200 + (rand() % 60);
    }
}

void Game::spawnObstacles() {
    if (--obstacleSpawnTimer <= 0) {
        Entity* obstacle = new Entity();
        int randomTexture = rand() % 3; 
        switch (randomTexture) {
            case 0:
                obstacle->texture = obstacleTexture1;
                break;
            case 1:
                obstacle->texture = obstacleTexture2;
                break;
            case 2:
                obstacle->texture = obstacleTexture3;
                break;
        }
        SDL_QueryTexture(obstacle->texture, NULL, NULL, &obstacle->w, &obstacle->h);
        obstacles.push_back(obstacle);
        obstacle->x = OBSTACLE_X;
        obstacle->y = FLOOR_Y - obstacle->h;
        obstacle->dx = -2;
        obstacle->health = 1;
        obstacle->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
        obstacle->side = SIDE_ALIEN;
        obstacleSpawnTimer = 30 + (rand() % 60);
    }
}

void Game::spawnFireballs() {
    if (--fireballSpawnTimer <= 0) {
        fireball();
        fireballSpawnTimer = 30 + (rand() % 60);
    }
}
/*
void Game::doFighters() {
    auto it = fighters.begin();
    it++;

    while (it != fighters.end()) {
        auto temp = it++;
        Entity* fighter = *temp;

        fighter->move();
        if (fighter->x < -fighter->w) {
            // Xóa fighter khi ra khỏi màn hình
            delete fighter;
            fighters.erase(temp);
            continue;
        }

        if (fighter->health <= 0) {
            // Nếu máu của fighter hết, xóa fighter
            delete fighter;
            fighters.erase(temp);
            continue;
        }
    }

    player.move();
    if (player.x < 0) player.x = 0;
    else if (player.x >= SCREEN_WIDTH - player.w)
        player.x = SCREEN_WIDTH - player.w;
    if (player.y < 0) player.y = 0;
    else if (player.y >= SCREEN_HEIGHT - player.h)
        player.y = SCREEN_HEIGHT - player.h;
}
*/

void Game::doBackground() {
    if (--backgroundX < -SCREEN_WIDTH) {
        backgroundX = 0;
    }
}

void Game::doStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x -= stars[i].speed;

        if (stars[i].x < 0) {
            stars[i].x = SCREEN_WIDTH + stars[i].x;
        }
    }
}

void Game::doLogic(int keyboard[]) {
    if (player.health <= 0) {
        // Nếu máu của player hết, reset game
        reset();
        return;
    }

    doBackground();
    doStarfield();
    doPlayer(keyboard);
    doObstacles();
    doBullets();
    doFireballs();
    doHelicopter();
    spawnObstacles();
    spawnFireballs();
    spawnHelicopter();
}

void Game::drawBackground(SDL_Renderer* renderer) {
    SDL_Rect dest;
    for (int x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(renderer, background, NULL, &dest);
    }
}

void Game::drawStarfield(SDL_Renderer* renderer) {
    for (int i = 0; i < MAX_STARS; i++) {
        int c = 32 * stars[i].speed;
        SDL_SetRenderDrawColor(renderer, c, c, c, 255);
        SDL_RenderDrawLine(renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }
}

void Game::draw(Graphics& graphics) {
    drawBackground(graphics.renderer);
    drawStarfield(graphics.renderer);

    // Vẽ player
    graphics.renderTexture(player.texture, player.x, player.y);

    // Vẽ obstacles
    for (Entity* obstacle : obstacles)
        graphics.renderTexture(obstacle->texture, obstacle->x, obstacle->y);

    // Vẽ bullets
    for (Entity* bullet : bullets)
        graphics.renderTexture(bullet->texture, bullet->x, bullet->y);

    // Vẽ fireballs
    for(Entity* fireball : fireballs) {
        graphics.renderAnimation(fireball->x, fireball->y, fireball); // Render fireball với clip hiện tại
        fireball->tick();
    }

    // Vẽ helicopter
    for(Entity* fireball : helicopters) {
        graphics.renderAnimation(fireball->x, fireball->y, fireball); // Render fireball với clip hiện tại
        fireball->tick();
    }
}


void Game::quit() {
    // Perform any cleanup needed when quitting the game
}
