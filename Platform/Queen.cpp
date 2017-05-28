#include <vector>
#include "ChessDebug.h"
#include "Move.h"
#include "Queen.h"
using namespace std;


Queen::Queen(PieceColor color) : Piece(color) {}

const string Queen::getSymbol() const {
	return QUEEN_SYMBOL;
}

vector<Move> Queen::getMoves(const Board &board, int x, int y) const {
	vector<Move> moves;
	return moves;
}
