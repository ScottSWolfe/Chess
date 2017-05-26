#include "Move.h"


Move::Move(SquareCoordinates start_coord, SquareCoordinates end_coord)
	: start_coordinate(start_coord), end_coordinate(end_coord)
{}

SquareCoordinates Move::getStartSquareCoord() const {
	return start_coordinate;
}

SquareCoordinates Move::getEndSquareCoord() const {
	return end_coordinate;
}

bool operator==(const Move &left, const Move &right) {
	if (left.start_coordinate == right.start_coordinate &&
		left.end_coordinate == right.end_coordinate)
	{
		return true;
	}
	return false;
}
