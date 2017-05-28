#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "Move.h"
#include "Position.h"
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

Square &Board::getSquare(Position pos) {
	return squares[getIndex(pos)];
}

const Square &Board::getSquare(Position pos) const {
	return squares[getIndex(pos)];
}

void Board::addPieceToSquare(Position pos, unique_ptr<const Piece> &piece) {
	getSquare(pos).setPiece(piece);
}

unique_ptr<const Piece> Board::removePieceFromSquare(Position pos) {
	return getSquare(pos).removePiece();
}

std::vector<Move> Board::getMoves(Position pos) const {
	const Piece *piece = getSquare(pos).getPiece();
	if (piece == nullptr) {
		throw invalid_argument("no piece on given square");
	}
	return piece->getMoves(*this, pos);
}

bool Board::isPiece(Position pos) const {
	if (getSquare(pos).getPiece() == nullptr) {
		return false;
	}
	return true;
}

const Piece *Board::getPiece(Position pos) const {
	return getSquare(pos).getPiece();
}

PieceColor Board::getPieceColor(Position pos) const {
	const Piece *piece = getSquare(pos).getPiece();
	if (piece == nullptr) {
		throw invalid_argument("square for given coordinates does not containe a piece");
	}
	return piece->getColor();
}

int Board::getDimension() const {
	return dimension;
}

int Board::getIndex(Position pos) const {
	return pos.y * dimension + pos.x;
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
