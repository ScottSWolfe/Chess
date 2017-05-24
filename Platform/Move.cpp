#include "Move.h"


Move::Move(SquareCoordinate start_coord, SquareCoordinate end_coord)
	: start_coordinate(start_coord), end_coordinate(end_coord)
{}

SquareCoordinate Move::getStartSquareCoord() const {
	return start_coordinate;
}

SquareCoordinate Move::getEndSquareCoord() const {
	return end_coordinate;
}
