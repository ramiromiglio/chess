#include <assert.h>
#include <algorithm>
#include "spritesheet.h"

SpriteSheet::SpriteSheet() {
}

SpriteSheet::SpriteSheet(const std::string &filepath, int width, int height) {
    if (! (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        m_IMG_up = false;
    }
    else {
        m_IMG_up = true;
        open(filepath, width, height);
    }
}

SpriteSheet::~SpriteSheet(){
    SDL_FreeSurface(m_surface);
    m_surface = nullptr;
}

void SpriteSheet::open(const std::string &filepath, int width, int height) {
    if (! m_IMG_up) {
        m_opened = false;
    }
    else {
        SDL_Surface *surface = IMG_Load(filepath.c_str());
        m_opened = (surface != nullptr);
        m_surface = surface;
    }
    m_wcells = width;
    m_hcells = height;
}

bool SpriteSheet::is_open() {
    return m_opened;
}

std::shared_ptr<Texture> SpriteSheet::cut(int x, int y) {
    /* Compruebo si la textura esta en cache para no cargarla en memoria mas de una vez */
    auto it = std::find_if(m_cached_textures.begin(), m_cached_textures.end(), [x, y](const TextureCache &cache) {
        if (cache.x == x && cache.y == y) {
            puts("Cache");
            return true;
        }
        else {
            return false;
        }
    });
    if (it != m_cached_textures.end()) {
        return it->ptr;
    }

    /* Corto y cargo la textura en la memoria */
    int w = m_surface->w / m_wcells;
    int h = m_surface->h / m_hcells;
    SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, m_surface->format->format);
    assert(surf);

    SDL_Rect r = {};
    r.x = x * w;
    r.y = y * h;
    r.w = w;
    r.h = h;

    int error = SDL_BlitSurface(m_surface, &r, surf, NULL);
    assert(error == 0);

    auto ptr = std::shared_ptr<Texture>(new Texture(surf));
    m_cached_textures.push_back(TextureCache(ptr, x, y));
    return ptr;
}