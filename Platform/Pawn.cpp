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

std::vector<Move> Pawn::getMoves(const Board &board, Position pos) const {
	vector<Move> moves;
	Position start(pos);
	Position end;

	// move forward one
	end = start.add(0, step());
	if (board.isPiece(end) == false) {
		moves.push_back(Move(start, end));
	}

	// move forward two
	if (start.y == startRow(board.getDimension())) {
		Position step_1 = start.add(0, step());
		Position step_2 = start.add(0, 2 * step());
		if (board.isPiece(step_1) == false && board.isPiece(step_2) == false) {
			moves.push_back(Move(start, step_2));
		}
	}

	// capture diagonally
	end = start.add(-1, step());
	if (board.isPiece(end) && board.getPieceColor(end) != getColor()) {
		moves.push_back(Move(start, end));
	}
	end = start.add(1, step());
	if (board.isPiece(end) && board.getPieceColor(end) != getColor()) {
		moves.push_back(Move(start, end));
	}

	// en passant

	return moves;
}

int Pawn::step() const {
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
