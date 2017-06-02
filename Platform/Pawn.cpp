#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Pawn.h"
#include "Move.h"
#include "MoveEffect.h"
#include "Position.h"
#include "Queen.h"
using namespace std;


Pawn::Pawn(PieceColor color)
	: Piece(color)
{}

std::unique_ptr<const Piece> Pawn::getCopy() const {
	return make_unique<const Pawn>(color);
}

const string Pawn::getSymbol() const {
	return PAWN_SYMBOL;
}

std::vector<Move> Pawn::getAvailableMoves(const GameState &state, Position start) const {
	vector<Move> moves;
	Position end;

	// move forward one
	end = start.add(0, step());
	if (state.inBounds(end) == true && state.isPiece(end) == false) {
		moves.push_back(Move(start, end));
	}

	// move forward two
	if (start.y == startRow(state.getBoardDimension())) {
		Position step_1 = start.add(0, step());
		Position step_2 = start.add(0, 2 * step());
		if (state.inBounds(step_1) && state.inBounds(step_2) &&
			state.isPiece(step_1) == false && state.isPiece(step_2) == false)
		{
			moves.push_back(Move(start, step_2));
		}
	}

	// capture diagonally
	end = start.add(-1, step());
	if (state.inBounds(end) && state.isPiece(end) && state.isOppPieceColor(end, color)) {
		moves.push_back(Move(start, end));
	}
	end = start.add(1, step());
	if (state.inBounds(end) && state.isPiece(end) && state.isOppPieceColor(end, color)) {
		moves.push_back(Move(start, end));
	}

	// en passant
	int delta_x = 0;
	if (isEnPassantAvailable(state, start, delta_x)) {
		addEnPassantMove(moves, start, delta_x);
	}

	return moves;
}

void Pawn::addMoveEffect(const GameState &state, Move &move) const {
	// check for en passant
	int delta_x = 0;
	if (isEnPassantAvailable(state, move.getStart(), delta_x)) {
		modifyEnPassantMove(move, delta_x);
		return;
	}

	// check for promotion
	if (move.getEnd().y == promotionRow(state.getBoardDimension())) {
		if (state.inBounds(move.getEnd())) {
			unique_ptr<const Piece> queen = make_unique<const Queen>(state.getPieceColor(move.getStart()));
			unique_ptr<const MoveEffect> effect = make_unique<const MoveEffect>(move.getEnd(), queen);
			move = Move(move.getStart(), move.getEnd(), effect);
			return;
		}
	}
}

bool Pawn::isEnPassantAvailable(const GameState &state, Position start, int &dst_delta_x) const {
	if (start.y == enPassantRow(state.getBoardDimension())) {
		const Move *last_move = state.getLastMove();
		if (last_move != nullptr) {
			Position last_move_start = last_move->getStart();
			Position last_move_end = last_move->getEnd();
			if (last_move_end == start.add(1, 0) || last_move_end == start.add(-1, 0)) {
				if (dynamic_cast<const Pawn*>(state.getPiece(last_move_end))) {
					dst_delta_x = last_move_end.x - start.x;
					if (last_move_start == start.add(dst_delta_x, 2 * step())) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Pawn::addEnPassantMove(vector<Move> &moves, Position start, int delta_x) const {
	Position end = start.add(delta_x, step());
	Position pos_piece_to_remove = start.add(delta_x, 0);
	auto effect = make_unique<const MoveEffect>(pos_piece_to_remove);
	moves.push_back(Move(start, end, effect));
}

void Pawn::modifyEnPassantMove(Move &move, int delta_x) const {
	Position start = move.getStart();
	Position end = start.add(delta_x, step());
	Position piece_to_remove = start.add(delta_x, 0);
	auto effect = make_unique<const MoveEffect>(piece_to_remove);
	move = (Move(start, end, effect));
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

int Pawn::promotionRow(int dimension) const {
	if (getColor() == PieceColor::BLACK) {
		return 0;
	}
	return dimension - 1;
}
