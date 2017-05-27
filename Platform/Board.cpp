#include <iostream>
#include "Board.h"
using namespace std;


Board::Board(int board_dimension) : dimension(board_dimension) {
	for (int i = 0; i < dimension * dimension; ++i) {
		Square square(getSquareColorByIndex(i));
		squares.emplace_back(square);
	}
}

Board::Board(const Board &other_board) :
	dimension(other_board.getDimension())
{
	for (int i = 0; i < dimension * dimension; ++i) {
		squares.emplace_back(other_board.squares[i]);
	}
}

Square &Board::getSquare(int x, int y) {
	return squares[convertCoordsToIndex(x, y)];
}

const Square &Board::getSquare(int x, int y) const {
	return squares[convertCoordsToIndex(x, y)];
}

void Board::addPieceToSquare(int x, int y, unique_ptr<const Piece> &piece) {
	squares[convertCoordsToIndex(x, y)].setPiece(piece);
}

unique_ptr<const Piece> Board::removePieceFromSquare(int x, int y) {
	return squares[convertCoordsToIndex(x, y)].removePiece();
}

bool Board::isPiece(int x, int y) const {
	if (squares[convertCoordsToIndex(x, y)].getPiece() == nullptr) {
		return false;
	}
	return true;
}

PieceColor Board::getPieceColor(int x, int y) const {
	const Piece *piece = squares[convertCoordsToIndex(x, y)].getPiece();
	if (piece == nullptr) {
		throw invalid_argument("square for given coordinates does not containe a piece");
	}
	return piece->getColor();
}

int Board::getDimension() const {
	return dimension;
}

int Board::convertCoordsToIndex(int x, int y) const {
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
