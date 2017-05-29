#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "Move.h"
#include "Piece.h"
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

SquareColor Board::getSquareColor(Position pos) const {
	return getSquare(pos).getColor();
}

bool Board::inBounds(Position pos) const {
	if (pos.x < 0 || pos.x >= dimension) {
		return false;
	}
	if (pos.y < 0 || pos.y >= dimension) {
		return false;
	}
	return true;
}

void Board::addPieceToSquare(Position pos, unique_ptr<const Piece> &piece) {
	getSquare(pos).setPiece(piece);
}

unique_ptr<const Piece> Board::removePieceFromSquare(Position pos) {
	return getSquare(pos).removePiece();
}

bool Board::isPiece(Position pos) const {
	if (getPiece(pos) == nullptr) {
		return false;
	}
	return true;
}

const Piece *Board::getPiece(Position pos) const {
	return getSquare(pos).getPiece();
}

PieceColor Board::getPieceColor(Position pos) const {
	return Piece::getPieceColor(getPiece(pos));
}

string Board::getPieceSymbol(Position pos) const {
	return Piece::getPieceSymbol(getPiece(pos));
}

bool Board::isOppPieceColor(Position pos, PieceColor color) const {
	if (getPieceColor(pos) == PieceColor::NO_PIECE) {
		return false;
	}
	return getPieceColor(pos) != color;
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

void Board::checkIfPieceIsNull(const Piece *piece) const {
	if (piece == nullptr) {
		throw invalid_argument("square does not contain a piece");
	}
}
