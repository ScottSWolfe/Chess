#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
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

std::vector<Move> Pawn::getMoves(const GameState &state, Position pos) const {
	vector<Move> moves;
	Position start(pos);
	Position end;

	// move forward one
	end = start.add(0, step());
	if (state.isPiece(end) == false) {
		moves.push_back(Move(start, end));
	}

	// move forward two
	if (start.y == startRow(state.getBoardDimension())) {
		Position step_1 = start.add(0, step());
		Position step_2 = start.add(0, 2 * step());
		if (state.isPiece(step_1) == false && state.isPiece(step_2) == false) {
			moves.push_back(Move(start, step_2));
		}
	}

	// capture diagonally
	end = start.add(-1, step());
	if (state.isPiece(end) && state.isOppPieceColor(end, color)) {
		moves.push_back(Move(start, end));
	}
	end = start.add(1, step());
	if (state.isPiece(end) && state.isOppPieceColor(end, color)) {
		moves.push_back(Move(start, end));
	}

	// en passant
	if (start.y == enPassantRow(state.getBoardDimension())) {
		const Move *last_move = state.getLastMove();
		if (last_move != nullptr) {
			if (addMoveIfEnPassantAvailable(moves, state, start, *last_move, 1) == false) {
				addMoveIfEnPassantAvailable(moves, state, start, *last_move, -1);
			}
		}
	}

	return moves;
}

bool Pawn::addMoveIfEnPassantAvailable(vector<Move> &moves, const GameState &state,
										Position start, const Move &last_move, int delta_x) const
{
	Position last_move_start = last_move.getStart();
	Position last_move_end = last_move.getEnd();
	if (last_move_end == start.add(delta_x, 0)) {
		if (dynamic_cast<const Pawn*>(state.getPiece(last_move_end))) {
			if (last_move_start == start.add(delta_x, 2 * step())) {
				Position end = start.add(delta_x, step());
				moves.push_back(Move(start, end));
				return true;
			}
		}
	}
	return false;
}

int Pawn::step() const {
	if (color == PieceColor::BLACK) {
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

int Pawn::enPassantRow(int dimension) const {
	if (getColor() == PieceColor::BLACK) {
		return 3;
	}
	return dimension - 4;
}
