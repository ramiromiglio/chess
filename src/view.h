#pragma once

#include "game_state.h"

class View {
public:
    View() = default;
    View(const View &) = delete;
    View &operator=(const View &) = delete;
    virtual ~View() {};
    virtual bool show() = 0;
    virtual void update(const GameState &st) = 0;
};