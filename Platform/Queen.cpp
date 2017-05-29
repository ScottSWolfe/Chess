#include <vector>
#include "ChessDebug.h"
#include "Move.h"
#include "Position.h"
#include "Queen.h"
using namespace std;


Queen::Queen(PieceColor color) : Piece(color) {}

const string Queen::getSymbol() const {
	return QUEEN_SYMBOL;
}

vector<Move> Queen::getMoves(const Board &board, Position pos) const {
	vector<Move> moves;
	getStraightMoves(moves, board, pos);
	getDiagonalMoves(moves, board, pos);
	return moves;
}
