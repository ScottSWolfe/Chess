#pragma once
#include <vector>
#include "Square.h"

class Board {
private:
	int dimension;
	std::vector<Square> squares;
public:
	Board(const int dimension);
	Square *getSquare(const int x, const int y);
};
