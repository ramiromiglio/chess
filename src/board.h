#pragma once

#include "board_iterator.h"
#include "board_square.h"
#include "board_point.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

class Board {
public:
    Board();
    Board(const Board &);
    Board &operator= (const Board &);
    void move(BoardPoint from, BoardPoint to);
    BoardSquare &get(BoardPoint point);
    BoardSquare &get(int r, int c);
    const BoardSquare &get(BoardPoint point) const;
    const BoardSquare &get(int r, int c) const;
    IteratorImpl begin() const;
    IteratorImpl end() const;

    template<typename Archive>
    void save(Archive &ar) const {
        std::vector<std::vector<BoardSquare>> v;
        for (int i = 0; i < 8; i++) {
            v.push_back({});
            for (int j = 0; j < 8; j++) {
                v[i].push_back(m_board[i][j]);
            }
        }
        ar(cereal::make_nvp("board", v));
    }
    template<typename Archive>
    void load(Archive &ar) {
        std::vector<std::vector<BoardSquare>> v;
        ar(cereal::make_nvp("board", v));
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                m_board[i][j] = v[i][j];
            }
        }
    }
private:
    BoardSquare m_board[8][8];
};