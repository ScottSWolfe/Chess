#include <iostream>
#include "Board.h"
using namespace std;


Board::Board() : dimension(8) {
	Board(dimension);
}

Board::Board(int board_dimension) : dimension(board_dimension) {
	for (int i = 0; i < dimension * dimension; ++i) {
		Square square(getSquareColorByIndex(i));
		//squares.emplace_back(new Square(getSquareColorByIndex(i)));
		squares.emplace_back(square);
	}
}

Square &Board::getSquare(int x, int y) {
	return squares[convertCoordinatesToIndex(x, y)];
}

const Square &Board::getSquare(int x, int y) const {
	return squares[convertCoordinatesToIndex(x, y)];
}

void Board::addPieceToSquare(int x, int y, unique_ptr<const Piece> &piece) {
	squares[convertCoordinatesToIndex(x, y)].setPiece(piece);
}

int Board::getDimension() const {
	return dimension;
}

int Board::convertCoordinatesToIndex(int x, int y) const {
	return y * dimension + x;
}

SquareColor Board::getSquareColorByIndex(int index) const {
	
	SquareColor color;
	
	int x = index % dimension;
	int y = index / dimension;

	if ((y + x) % 2 == 0) {
		color = SquareColor::DARK;
	}
	else {
		color = SquareColor::LIGHT;
	}

	return color;
}
