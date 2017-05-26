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
