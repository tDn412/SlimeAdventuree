#include "TextObject.h"

TextObject::TextObject(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
    : renderer(renderer), font(font), text(text), x(x), y(y), texture(nullptr) {
    createTexture();
}

TextObject::~TextObject() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void TextObject::createTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void TextObject::render() {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void TextObject::setText(const std::string& newText) {
    text = newText;
    createTexture();
}
