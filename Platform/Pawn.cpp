#include <vector>
#include "ChessDebug.h"
#include "Board.h"
#include "Pawn.h"
#include "Move.h"
#include "Position.h"
using namespace std;


Pawn::Pawn(PieceColor color)
	: Piece(color)
{}

const string Pawn::getSymbol() const {
	return PAWN_SYMBOL;
}

std::vector<Move> Pawn::getMoves(const Board &board, int x, int y) const {
	vector<Move> moves;
	Position start(x, y);
	Position end;

	// move forward one
	if (!board.isPiece(x, y + direction())) {
		end = Position(x, y + direction());
		moves.push_back(Move(start, end));
	}

	// move forward two
	if (y == startRow(board.getDimension())) {
		if (!board.isPiece(x, y + direction()) && !board.isPiece(x, y + 2 * direction())) {
			end = Position(x, y + 2 * direction());
			moves.push_back(Move(start, end));
		}
	}

	// capture diagonally
	if (board.isPiece(x - 1, y + direction()) &&
		board.getPieceColor(x - 1, y + direction()) != getColor()) {
		end = Position(x - 1, y + direction());
		moves.push_back(Move(start, end));
	}
	if (board.isPiece(x + 1, y + direction()) &&
		board.getPieceColor(x + 1, y + direction()) != getColor()) {
		end = Position(x + 1, y + direction());
		moves.push_back(Move(start, end));
	}

	// en passant

	return moves;
}

int Pawn::direction() const {
	if (getColor() == PieceColor::BLACK) {
		return -1;
	}
	return 1;
}

int Pawn::startRow(int dimension) const {
	if (getColor() == PieceColor::BLACK) {
		return dimension - 2;
	}
	return 1;
}
