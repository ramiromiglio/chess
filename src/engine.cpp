#include "engine.h"

Engine::Engine() {}

bool Engine::is_valid_move(const BoardPoint &from, const BoardPoint &to) const {
    return is_valid_move(Move(from, to));
}

bool Engine::is_valid_move(const Move &move) const {
    BoardPoint f = move.from;
    BoardPoint t = move.to;

    if (f == t) {
        return false;
    }

    if (! m_white_player_turn) {
        //f.rotate();
        //t.rotate();
    }

    const BoardSquare &f_state = m_board.get (f);
    const BoardSquare &t_state = m_board.get (t);
    
    if (m_white_player_turn != f_state.piece_is_white) {
        return false;
    }
    if (t_state.occupied && f_state.piece_is_white == t_state.piece_is_white) {
        // Enroque?
        // TODO
        return false;
    }

    

    if (f_state.piece_type == PieceType::R) {
        if (adjacent (f, t)) {
            return true;
        }
    }
    else if (f_state.piece_type == PieceType::D) {
        if (same_row (f, t) || same_column (f, t)) {
            if (linear_move_clear (f, t)) {
                return true;
            }
        }
        else if (same_diagonal (f, t) && diagonal_move_clear (f, t)) {
            return true;
        }
    }
    else if (f_state.piece_type == PieceType::T) {
        if ((same_row (f, t) || same_column (f, t)) && linear_move_clear (f, t)) {
            return true;
        }
    }
    else if (f_state.piece_type == PieceType::A) {
        if (same_diagonal (f, t) && diagonal_move_clear (f, t)) {
            return true;
        }
    }
    else if (f_state.piece_type == PieceType::C) {
        if (valid_knight_move (f, t)) {
            return true;
        }
    }
    else if (f_state.piece_type == PieceType::P) {
        if (! m_white_player_turn) {
            f.rotate();
            t.rotate();
        }

        if (t_state.occupied) {
            // Peon come en diagonal
            if (f.row() + 1 == t.row() && (f.col() == t.col() + 1 || f.col() == t.col() - 1)) {
                return true;
            }
            // Peon come "al paso"
            // TODO
        }
        else {
            // Peon avanza una casilla
            if (f.row() + 1 == t.row() && f.col() == t.col()) {
                return true;
            }
            // Peon avanza dos casillas si aun no movio desde que comenzo la partida
            if (f.row() + 2 == t.row() && f.col() == t.col() && f.row() == 1) {
                return true;
            }
        }
    }

    return false;
}

void Engine::move(const Move &move) {
    if (is_valid_move(move)) {
        m_board.move(move.from, move.to);
        turn();
    }
}

void Engine::move(const BoardPoint &from, const BoardPoint &to) {
    move(Move(from, to));
}

bool Engine::same_row(BoardPoint f, BoardPoint t) const {
    return f.row() == t.row();
}

bool Engine::same_column(BoardPoint f, BoardPoint t) const {
    return f.col() == t.col();
}

bool Engine::same_diagonal(BoardPoint f, BoardPoint t) const {
    return std::abs(f.row() - t.row()) == std::abs(f.col() - t.col());
}

bool Engine::valid_knight_move(BoardPoint f, BoardPoint t) const {
    if (std::abs(f.row() - t.row()) == 2) {
        return std::abs(f.col() - t.col()) == 1;
    }
    else
    if (std::abs(f.col() - t.col()) == 2) {
        return std::abs(f.row() - t.row()) == 1;
    }
    else {
        return false;
    }
}

bool Engine::adjacent(BoardPoint f, BoardPoint t) const {
    const int row_dif = std::abs(f.row() - t.row());
    const int col_dif = std::abs(f.col() - t.col());
    if (row_dif + col_dif < 2) {
        return true;
    }
    else
    if (row_dif + col_dif == 2) {
        return row_dif == 1;
    }
    return false;
}

bool Engine::diagonal_move_clear(BoardPoint f, BoardPoint t) const {
    if (! same_diagonal (f, t)) {
        return false;
    }
    const int row_dir = f.row() < t.row() ? 1 : -1;
    const int col_dir = f.col() < t.col() ? 1 : -1;
    int steps = std::abs(t.row() - f.row());
    int row_off = row_dir;
    int col_off = col_dir;

    for (; steps > 1; steps--) {
        if (m_board.get (f.row() + row_off, f.col() + col_off).occupied) {
            break;
        }
        row_off += row_dir;
        col_off += col_dir;
    }

    if (steps == 1) {
        return true;
    }
    return false;
}

bool Engine::linear_move_clear(BoardPoint f, BoardPoint t) const {
    if (same_row (f, t)) {
        const int dir = (f.col() < t.col()) ? 1 : -1;
        int pos = dir;
        for (; (f.col() + pos) != t.col(); pos += dir) {
            if (m_board.get (f.row(), f.col() + pos).occupied) {
                break;
            }
        }
        if (f.col() + pos == t.col()) {
            return true;
        }
    }
    else
    if (same_column (f, t)) {
        const int dir = (f.row() < t.row()) ? 1 : -1;
        int pos = dir;
        for (; (f.row() + pos) != t.row(); pos += dir) {
            if (m_board.get (f.row() + pos, f.col()).occupied) {
                break;
            }
        }
        if (f.row() + pos == t.row()) {
            return true;
        }
    }
    return false;
}

void Engine::turn() {
    m_white_player_turn = !m_white_player_turn;
}