#include "move.h"

Move::Move() {}

Move::Move(const BoardPoint &from, const BoardPoint &to) {
    this->from = from;
    this->to = to;
}