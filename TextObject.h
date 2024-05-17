#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextObject {
public:
    TextObject(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
    ~TextObject();

    void setText(const std::string& text);
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect position;
    TTF_Font* font;
    std::string text;
    int x,y;
    void createTexture();
};

#endif // TEXTOBJECT_H