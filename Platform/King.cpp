#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "King.h"
#include "Move.h"
#include "Position.h"
using namespace std;


King::King(PieceColor color) : Piece(color) {}

std::unique_ptr<const Piece> King::getCopy() const {
	return make_unique<const King>(color);
}

const string King::getSymbol() const {
	return KING_SYMBOL;
}

vector<Move> King::getMoves(const GameState &state, Position start) const {
	vector<Move> moves;
	for (int delta_y = -1; delta_y <= 1; delta_y++) {
		for (int delta_x = -1; delta_x <= 1; delta_x++) {
			Position end = start.add(delta_x, delta_y);
			if (state.inBounds(end) &&
				(state.isPiece(end) == false || state.isOppPieceColor(end, color)))
			{
				moves.push_back(Move(start, end));
			}
		}
	}
	return moves;
}

void King::checkForAndAddMoveEffect(const GameState &state, Move &move) const {
	// check for castle
	return;
}
