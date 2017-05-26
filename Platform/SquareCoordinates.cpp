#include "SquareCoordinates.h"


SquareCoordinates::SquareCoordinates()
	: x(-1), y(-1)
{}

SquareCoordinates::SquareCoordinates(int x, int y)
	: x(x), y(y)
{}

bool SquareCoordinates::operator==(const SquareCoordinates &other_coordinates) const {
	if (this->x == other_coordinates.x &&
		this->y == other_coordinates.y)
	{
		return true;
	}
	return false;
}

bool SquareCoordinates::empty() const {
	if (x == -1 || y == -1) {
		return true;
	}
	return false;
}
