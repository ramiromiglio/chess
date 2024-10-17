#pragma once

#include <SDL2/SDL_net.h>
#include <string>
#include "board.h"
#include "move.h"
#include "game_state.h"

class Engine {
protected:
    Board m_board;
    bool m_white_player_turn = true;
    void turn();
    //SDLNetLogger m_logger;
public:
    Engine();
    bool is_valid_move(const Move &move) const;
    bool is_valid_move(const BoardPoint &from, const BoardPoint &to) const;
    void move(const Move &move);
    void move(const BoardPoint &from, const BoardPoint &to);

    const Board &board() { return m_board; }
    bool is_white_turn() const { return m_white_player_turn; }
    GameState get_state() {
        GameState st;
        st.m_board = m_board;
        st.m_white_turn = m_white_player_turn;
        return st;
    }
    void set_state(const GameState &st) {
        m_board = st.m_board;
        m_white_player_turn = st.m_white_turn;
    }
private:
    bool same_row(BoardPoint f, BoardPoint t) const;
    bool same_column(BoardPoint f, BoardPoint t) const;
    bool same_diagonal(BoardPoint f, BoardPoint t) const;
    bool valid_knight_move(BoardPoint f, BoardPoint t) const;
    bool adjacent(BoardPoint f, BoardPoint t) const;
    bool diagonal_move_clear(BoardPoint f, BoardPoint t) const;
    bool linear_move_clear(BoardPoint f, BoardPoint t) const;
};