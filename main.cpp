#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
#include "logic.cpp"
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(0));

    Graphics graphics;
    graphics.init();

    Input input;
    input.init();
    Game game;
    game.init(graphics);

    while (1) {
        graphics.prepareScene();

        input.get();

        game.doLogic(input.keyboard);
        game.draw(graphics);

        graphics.presentScene();

        SDL_Delay(1000 / FRAME_PER_SECOND); // Chú ý thời gian delay cho mỗi frame
    }

    graphics.quit();
    return 0;
}