#pragma once

#include <SDL2/SDL.h>

class Texture {
public:
    Texture(const Texture &) = delete;
    Texture(Texture &&) = delete;
    Texture &operator= (const Texture &) = delete;
    Texture &operator= (Texture &&) = delete;
    ~Texture();
    int width();
    int height();
    void draw(SDL_Surface *surface, SDL_Rect rect) {
        SDL_BlitScaled(m_surface, nullptr, surface, &rect);
    }
private:
    friend class SpriteSheet;
    Texture(SDL_Surface *surface);
    SDL_Surface *m_surface;
};