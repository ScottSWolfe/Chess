#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "Move.h"
using namespace std;


Board::Board(int board_dimension)
	: dimension(board_dimension)
{
	if (board_dimension > 99) {
		throw invalid_argument("board dimension is too large");
	}
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
	getSquare(x, y).setPiece(piece);
}

unique_ptr<const Piece> Board::removePieceFromSquare(int x, int y) {
	return getSquare(x, y).removePiece();
}

std::vector<Move> Board::getMoves(int x, int y) const {
	const Piece *piece = getSquare(x, y).getPiece();
	if (piece == nullptr) {
		throw invalid_argument("no piece on given square");
	}
	return piece->getMoves(*this, x, y);
}

bool Board::isPiece(int x, int y) const {
	if (getSquare(x, y).getPiece() == nullptr) {
		return false;
	}
	return true;
}

const Piece *Board::getPiece(int x, int y) const {
	return getSquare(x, y).getPiece();
}

PieceColor Board::getPieceColor(int x, int y) const {
	const Piece *piece = getSquare(x, y).getPiece();
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
