#pragma once

#include "SquareCoordinates.h"


class Move {

public:
	Move(SquareCoordinates start_coord, SquareCoordinates end_coord);
	SquareCoordinates getStartSquareCoord() const;
	SquareCoordinates getEndSquareCoord() const;

private:
	SquareCoordinates start_coordinate;
	SquareCoordinates end_coordinate;

};
