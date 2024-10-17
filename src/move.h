#pragma once

#include "board_point.h"

struct Move {
    Move();
    Move(const BoardPoint &from, const BoardPoint &to);
    BoardPoint from;
    BoardPoint to;
};