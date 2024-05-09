#ifndef _DEFS__H
#define _DEFS__H

#define WINDOW_TITLE "Hello World!"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   16
#define PLAYER_RELOAD          8
#define MAX_KEYBOARD_KEYS 350
#define FLOOR_Y 560
#define OBSTACLE_X 1230
#define SIDE_PLAYER 0
#define SIDE_ALIEN  1
#define gravity 2
#define FRAME_PER_SECOND 60

#define OBSTACLE_BULLET_SPEED    8

#define MAX_STARS   500

#define BG_COLOR_R 96
#define BG_COLOR_G 128
#define BG_COLOR_B 255
#define BG_COLOR_A 255

const char* FIREBALL_SPRITE_FILE = "img\\shot_fireball.png";
const int FIREBALL_CLIPS[][4] = {
    {0, 0, 32, 32},
    {32,0, 32, 32},
    {64,0, 32, 32},
    {96,0, 32, 32}
};

const int FIREBALL_FRAMES = sizeof(FIREBALL_CLIPS)/sizeof(int)/4;

#endif
