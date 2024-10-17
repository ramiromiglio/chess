#pragma once

#include "board.h"
#include <fstream>
#include <cereal/archives/json.hpp>
#include <iostream>

struct GameState {
    friend class Engine;
    GameState();

    void save_to_file(const char *fname);
    void load_from_file(const char *fname);
    const Board &board() const;
    bool white_turn();
private:
    Board m_board;
    bool m_white_turn;
};