#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Position.h"
#include "Queen.h"
using namespace std;


Queen::Queen(PieceColor color) : Piece(color) {}

const string Queen::getSymbol() const {
	return QUEEN_SYMBOL;
}

vector<Move> Queen::getMoves(const GameState &state, Position pos) const {
	vector<Move> moves;
	getStraightMoves(moves, state, pos);
	getDiagonalMoves(moves, state, pos);
	return moves;
}
