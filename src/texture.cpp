#include "texture.h"

Texture::Texture(SDL_Surface *surface) {
    m_surface = surface;
}

Texture::~Texture() {
    SDL_FreeSurface(m_surface);
    m_surface = nullptr;
}

int Texture::width() {
    return m_surface->w;
}

int Texture::height() {
    return m_surface->h;
}