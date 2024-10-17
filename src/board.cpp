#include <algorithm>
#include <string.h>
#include "board.h"

Board::Board() {        
    m_board[0][0] = BoardSquare(PieceType::T, 'w', true);
    m_board[0][1] = BoardSquare(PieceType::C, 'w', true);
    m_board[0][2] = BoardSquare(PieceType::A, 'w', true);
    m_board[0][3] = BoardSquare(PieceType::D, 'w', true);
    m_board[0][4] = BoardSquare(PieceType::R, 'w', true);
    m_board[0][5] = BoardSquare(PieceType::A, 'w', true);
    m_board[0][6] = BoardSquare(PieceType::C, 'w', true);
    m_board[0][7] = BoardSquare(PieceType::T, 'w', true);

    int r = 1;
    int c = 0;
    std::for_each(std::begin(m_board[r]), std::end(m_board[r]), [r, &c] (BoardSquare &s) {
        s = BoardSquare(PieceType::P, 'w', true);
    });

    r = 6;
    c = 0;
    std::for_each(std::begin(m_board[r]), std::end(m_board[r]), [r, &c] (BoardSquare &s) {
        s = BoardSquare(PieceType::P, 'b', true);
    });

    m_board[7][0] = BoardSquare(PieceType::T, 'b', true);
    m_board[7][1] = BoardSquare(PieceType::C, 'b', true);
    m_board[7][2] = BoardSquare(PieceType::A, 'b', true);
    m_board[7][3] = BoardSquare(PieceType::D, 'b', true);
    m_board[7][4] = BoardSquare(PieceType::R, 'b', true);
    m_board[7][5] = BoardSquare(PieceType::A, 'b', true);
    m_board[7][6] = BoardSquare(PieceType::C, 'b', true);
    m_board[7][7] = BoardSquare(PieceType::T, 'b', true);                    
}

Board::Board(const Board &other) {
    //*this = other;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_board[i][j] = other.m_board[i][j];
        }
    }
}

Board &Board::operator= (const Board &other) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_board[i][j] = other.m_board[i][j];
        }
    }
    return *this;
}

void Board::move(BoardPoint from, BoardPoint to) {
    BoardSquare &fs = get(from);
    BoardSquare &ts = get(to);
    ts.piece_type = fs.piece_type;
    ts.piece_is_white = fs.piece_is_white;
    ts.occupied = true;
    fs.occupied = false;
    fs.piece_is_white = false;
    puts("Board::move");
}

BoardSquare &Board::get(BoardPoint sq) {
    return m_board[sq.row()][sq.col()];
}

BoardSquare &Board::get(int r, int c) {
    return m_board[r][c];
}

const BoardSquare &Board::get(BoardPoint sq) const {
    return m_board[sq.row()][sq.col()];
}

const BoardSquare &Board::get(int r, int c) const {
    return m_board[r][c];
}

IteratorImpl Board::begin() const {
    return IteratorImpl(m_board, 0);
}

IteratorImpl Board::end() const {
    return IteratorImpl(m_board, 8 * 8);
}