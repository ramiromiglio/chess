#pragma once

#include <SDL2/SDL.h>

enum PieceType : unsigned int {
    R = 0, // rey
    D = 1, // dama
    T = 2, // torre
    A = 3, // alfil
    C = 4, // caballo
    P = 5, // peon
    NONE = 255,
};