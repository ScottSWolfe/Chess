#include <vector>
#include "ChessDebug.h"
#include "Bishop.h"
#include "Move.h"
#include "Position.h"
using namespace std;


Bishop::Bishop(PieceColor color) : Piece(color) {}

const string Bishop::getSymbol() const {
	return BISHOP_SYMBOL;
}

vector<Move> Bishop::getMoves(const Board &board, Position pos) const {
	vector<Move> moves;
	getDiagonalMoves(moves, board, pos);
	return moves;
}
