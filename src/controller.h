#pragma once

#include "view.h"

class Game;

class Controller {
public:
    Controller(Game &game, std::shared_ptr<View> view) : m_game(game), m_view(view) { }

    virtual void update() = 0;
    virtual bool closed() = 0;
protected:
    std::shared_ptr<View> m_view;
    Game &m_game;
};