#pragma once

#include <vector>
#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

class SpriteSheet {
public:
    SpriteSheet();
    SpriteSheet(const std::string &filepath, int width, int height);
    ~SpriteSheet();
    void open(const std::string &filepath, int width, int height);
    bool is_open();

    std::shared_ptr<Texture> cut(int x, int y);
private:
    struct TextureCache {
        TextureCache(std::shared_ptr<Texture> ptr, int x, int y) : ptr(ptr), x(x), y(y) { }
        std::shared_ptr<Texture> ptr;
        int x;
        int y;
    };

    std::vector<TextureCache> m_cached_textures;
    SDL_Surface *m_surface = nullptr;
    bool m_opened = false;
    bool m_IMG_up = false;
    int m_wcells = 0;
    int m_hcells = 0;
};