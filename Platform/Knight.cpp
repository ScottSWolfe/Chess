#include <vector>
#include "ChessDebug.h"
#include "Knight.h"
#include "Move.h"
using namespace std;


Knight::Knight(PieceColor color) : Piece(color) {}

const string Knight::getSymbol() const {
	return KNIGHT_SYMBOL;
}

vector<Move> Knight::getMoves(const Board &board, int x, int y) const {
	vector<Move> moves;
	return moves;
}
