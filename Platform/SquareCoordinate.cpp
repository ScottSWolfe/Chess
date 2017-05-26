#include "SquareCoordinate.h"


SquareCoordinate::SquareCoordinate()
	: x(-1), y(-1)
{}

SquareCoordinate::SquareCoordinate(int x, int y)
	: x(x), y(y)
{}

bool SquareCoordinate::empty() const {
	if (x == -1 || y == -1) {
		return true;
	}
	return false;
}
