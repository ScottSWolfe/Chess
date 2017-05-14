#include "Board.h"

Board::Board(const int new_dimension) {
	dimension = new_dimension;
	for (int i = 0; i < dimension * dimension; ++i) {
		Square square;
		squares.emplace_back(square);
	}
}

Square *Board::getSquare(const int x, const int y) {
	return &squares[convertCoordinatesToIndex(x, y, dimension)];
}

void Board::addPieceToSquare(const int x, const int y, Piece *piece) {
	squares[convertCoordinatesToIndex(x, y, dimension)].setPiece(piece);
}

inline int Board::convertCoordinatesToIndex(const int x, const int y, const int dimension) {
	return y * dimension + x;
}
