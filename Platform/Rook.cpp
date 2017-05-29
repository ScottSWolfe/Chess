#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Position.h"
#include "Rook.h"
using namespace std;


Rook::Rook(PieceColor color) : Piece(color) {}

const string Rook::getSymbol() const {
	return ROOK_SYMBOL;
}

vector<Move> Rook::getMoves(const GameState &state, Position pos) const {
	vector<Move> moves;
	getStraightMoves(moves, state, pos);
	return moves;
}
