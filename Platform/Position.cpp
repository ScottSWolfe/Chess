#include "ChessDebug.h"
#include "Position.h"


Position::Position()
	: x(-1), y(-1)
{}

Position::Position(int x, int y)
	: x(x), y(y)
{}

bool Position::operator==(const Position &other_coordinates) const {
	if (this->x == other_coordinates.x &&
		this->y == other_coordinates.y)
	{
		return true;
	}
	return false;
}

bool Position::empty() const {
	if (x == -1 || y == -1) {
		return true;
	}
	return false;
}
