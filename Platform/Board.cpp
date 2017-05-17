#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(const int board_dimension) : dimension(board_dimension) {
	for (int i = 0; i < dimension * dimension; ++i) {
		Square square(getSquareColorByIndex(i));
		squares.emplace_back(square);
	}
}

Square *Board::getSquare(const int x, const int y) {
	return &squares[convertCoordinatesToIndex(x, y)];
}

void Board::addPieceToSquare(const int x, const int y, Piece *piece) {
	squares[convertCoordinatesToIndex(x, y)].setPiece(piece);
}

int Board::getDimension() {
	return dimension;
}

inline int Board::convertCoordinatesToIndex(const int x, const int y) {
	return y * dimension + x;
}

SquareColor Board::getSquareColorByIndex(const int index) {
	SquareColor color;

	int x = index % dimension;
	int y = index / dimension;

	if (y % 2 == 0) {
		if (x % 2 == 0) {
			color = SquareColor::DARK;
		}
		else {
			color = SquareColor::LIGHT;
		}
	}
	else {
		if (x % 2 == 0) {
			color = SquareColor::LIGHT;
		}
		else {
			color = SquareColor::DARK;
		}
	}
	return color;
}
