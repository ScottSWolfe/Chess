#pragma once

#include <memory>
#include <vector>
#include "Square.h"
class Piece;


class Board {

public:
	Board(int board_dimension);
	Square &getSquare(int x, int y);
	const Square &getSquare(int x, int y) const;
	void addPieceToSquare(int x, int y, std::unique_ptr<const Piece> &piece);
	std::unique_ptr<const Piece> removePieceFromSquare(int x, int y);
	int getDimension() const;

private:
	const int dimension;
	std::vector<Square> squares;
	int convertCoordinatesToIndex(int x, int y) const;
	SquareColor getSquareColorByIndex(int index) const;

};
