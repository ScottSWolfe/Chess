#include <vector>
#include "ChessDebug.h"
#include "Move.h"
#include "Rook.h"
using namespace std;


Rook::Rook(PieceColor color) : Piece(color) {}

const string Rook::getSymbol() const {
	return ROOK_SYMBOL;
}

vector<Move> Rook::getMoves(const Board &board, int x, int y) const {
	vector<Move> moves;
	return moves;
}
