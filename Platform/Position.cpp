#include "ChessDebug.h"
#include "Position.h"

namespace chess {


Position::Position()
    : x(-1), y(-1)
{}

Position::Position(int x, int y)
    : x(x), y(y)
{}

Position::Position(const Position &pos)
    : x(pos.x), y(pos.y)
{}

bool Position::operator==(const Position &other) const {
    if (this->x == other.x &&
        this->y == other.y)
    {
        return true;
    }
    return false;
}

bool Position::operator!=(const Position &other) const {
    if (*this == other) {
        return false;
    }
    return true;
}

Position Position::add(int delta_x, int delta_y) const {
    return Position(x + delta_x, y + delta_y);
}

bool Position::empty() const {
    if (x == -1 || y == -1) {
        return true;
    }
    return false;
}


}
