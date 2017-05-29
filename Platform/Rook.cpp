#include <vector>
#include "ChessDebug.h"
#include "Move.h"
#include "Position.h"
#include "Rook.h"
using namespace std;


Rook::Rook(PieceColor color) : Piece(color) {}

const string Rook::getSymbol() const {
	return ROOK_SYMBOL;
}

vector<Move> Rook::getMoves(const Board &board, Position pos) const {
	vector<Move> moves;
	getStraightMoves(moves, board, pos);
	return moves;
}
