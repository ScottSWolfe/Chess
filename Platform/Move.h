#pragma once

#include "SquareCoordinate.h"


class Move {

public:
	Move(SquareCoordinate start_coord, SquareCoordinate end_coord);
	SquareCoordinate getStartSquareCoord() const;
	SquareCoordinate getEndSquareCoord() const;

private:
	SquareCoordinate start_coordinate;
	SquareCoordinate end_coordinate;

};
