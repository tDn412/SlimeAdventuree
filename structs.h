#ifndef _APP__H
#define _APP__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include<iostream>
#include<vector>
using namespace std;
const float GRAVITY = 1.0f;

struct Entity {
	int x;
	int y;
	int w;
	int h;
    float dx;
	float dy;
	float JUMP_SPEED = 20;
	float jumpAcceleration = 2;
	bool isJumping = false;
	int side;
	int health;
	int reload;
	SDL_Texture *texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void initAnimation(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;

        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }

    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }

	bool collides(Entity* other) {
	    return (max(x, other->x) < min(x + w, other->x + other->w))
	        && (max(y, other->y) < min(y + h, other->y + other->h));
	}
	bool onGround = true;
	void move() {
	    x += dx;
	    y += dy;
	}

	void playermove(){
		dy += gravity;
		x += dx;
		y += dy;

        // Đảm bảo rằng nhân vật không rơi ra khỏi màn hình
        if (y > FLOOR_Y - h || y <= 0) {
            y = FLOOR_Y - h;
            onGround = true;
            dy = 0;
        }
	}

    void jump() {
		if(onGround){
		dy = -48.0f;
		onGround = false;
		}
    }

	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}
};

struct Explosion {
	float x;
	float y;
	float dx;
	float dy;
	int r, g, b, a;
};

struct Debris {
	float x;
	float y;
	float dx;
	float dy;
	SDL_Rect rect;
	SDL_Texture *texture;
	int life;
};

struct Star {
	int x;
	int y;
	int speed;
};
#endif // _APP__H
