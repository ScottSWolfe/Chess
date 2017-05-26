#include "SquareCoordinates.h"


SquareCoordinates::SquareCoordinates()
	: x(-1), y(-1)
{}

SquareCoordinates::SquareCoordinates(int x, int y)
	: x(x), y(y)
{}

bool SquareCoordinates::empty() const {
	if (x == -1 || y == -1) {
		return true;
	}
	return false;
}
