#pragma once

#include <vector>
#include "Square.h"

class Piece;


class Board {

public:
	Board(const int board_dimension);
	Square *getSquare(const int x, const int y);
	void addPieceToSquare(const int x, const int y, Piece *piece);
	int getDimension();

private:
	const int dimension;
	std::vector<Square> squares;
	inline int convertCoordinatesToIndex(const int x, const int y);
	SquareColor getSquareColorByIndex(const int index);

};
