#pragma once

struct BoardPoint {
    BoardPoint() {}
    BoardPoint(int r, int c) {
        this->m_row = r;
        this->m_col = c;
    }
    void rotate() {
        m_row = 7 - m_row;
        m_col = 7 - m_col;
    }
    bool operator == (const BoardPoint &o) const {
        return m_row == o.m_row && m_col == o.m_col;
    }
    bool operator != (const BoardPoint &other) const {
        return !(*this == other);
    }
    int row() const { return m_row; }
    int col() const { return m_col; }
private:
    int m_row = 0;
    int m_col = 0;
};