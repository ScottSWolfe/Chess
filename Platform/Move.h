#pragma once

#include "SquareCoordinates.h"


class Move {

public:
	Move(SquareCoordinates start_coord, SquareCoordinates end_coord);
	friend bool operator==(const Move &left, const Move &right);
	SquareCoordinates getStartCoords() const;
	SquareCoordinates getEndCoords() const;

private:
	SquareCoordinates start_coordinate;
	SquareCoordinates end_coordinate;

};

bool operator==(const Move &left, const Move &right);
