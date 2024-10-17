#pragma once

#include "board_square.h"
#include "utils.h"

struct Iterator {
    Iterator(const BoardSquare &sq_state, const int row, const int col) :
        sq_state(sq_state),
        row(row),
        col(col) {}
    const BoardSquare &sq_state;
    const int row;
    const int col;
};

struct IteratorImpl : public std::iterator<std::input_iterator_tag, Iterator, ptrdiff_t, Iterator*, Iterator&> {        
    explicit IteratorImpl(const BoardSquare (&board)[8][8], const int pos) : m_board(board) {
        ASSERT (pos >= 0 && pos <= 8 * 8);
        m_pos = pos;
    }
    IteratorImpl& operator ++() {
        m_pos++;
        return *this;
    }
    IteratorImpl operator ++ (int n) {
        return IteratorImpl(m_board, m_pos + n);
    }
    bool operator == (IteratorImpl &other) const {
        return m_pos == other.m_pos;
    }
    bool operator != (IteratorImpl &other) const {
        return !(*this == other);
    }
    const Iterator operator * () const {
        int r = m_pos / 8;
        int c = m_pos % 8;
        return Iterator(m_board[r][c], r, c);
    }
private:
    const BoardSquare (&m_board)[8][8];
    int m_pos;
};