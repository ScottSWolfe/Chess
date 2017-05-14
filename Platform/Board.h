#pragma once
#include <vector>
#include "Square.h"

class Board {
private:
	int dimension;
	std::vector<Square> squares;
	inline int Board::convertCoordinatesToIndex(const int x, const int y, const int dimension);
public:
	Board(const int dimension);
	Square *getSquare(const int x, const int y);
	void addPieceToSquare(const int x, const int y, Piece *piece);
};
