#include "game_state.h"

GameState::GameState() {}

void GameState::save_to_file(const char *fname) {
    std::ofstream fs(fname);
    cereal::JSONOutputArchive ar(fs);
    ar(m_board, CEREAL_NVP(m_white_turn));
}

void GameState::load_from_file(const char *fname) {
    std::ifstream fs(fname);
    cereal::JSONInputArchive ar(fs);
    ar(m_board, CEREAL_NVP(m_white_turn));
}

const Board &GameState::board() const {
    return m_board;
}

bool GameState::white_turn() {
    return m_white_turn;
}