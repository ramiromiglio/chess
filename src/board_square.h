#pragma once

#include "piece.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

struct BoardSquare {
    BoardSquare() {}
    BoardSquare(PieceType piece_type, char color, bool occupied) {
        this->piece_type = piece_type;
        this->piece_is_white = color == 'w';
        this->occupied = occupied;
    }
    PieceType piece_type;
    bool piece_is_white = false;
    bool occupied = false;

    template<typename Archive>
    void save(Archive &ar) const {
        ar(CEREAL_NVP(occupied));
        if (occupied) {
            ar(CEREAL_NVP(piece_type));
            ar(CEREAL_NVP(piece_is_white));
        }
    }

    template<typename Archive>
    void load(Archive &ar) {
        ar(cereal::make_nvp("occupied", occupied));
        if (occupied) {
            ar(cereal::make_nvp("piece_type", piece_type));
            ar(cereal::make_nvp("piece_is_white", piece_is_white));
        }
    }
};